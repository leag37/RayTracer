//*************************************************************************************************
// Title: SceneRenderer.cpp
// Author: Gael Huber
// Description: Implementation file for SceneRenderer
//*************************************************************************************************
#include "SceneRenderer.h"
#include "ChunkData.h"
#include <Windows.h>
#include <gl/GL.h>

namespace SuperTrace
{
    DWORD WINAPI RenderWorker(LPVOID lpParam);

    /** Default constructor
    */
    SceneRenderer::SceneRenderer()
    :   _numChunks(0)
    { }

    /** Destructor
    */
    SceneRenderer::~SceneRenderer()
    { }

    /** Set the number of chunks
    * @param
    *   numChunks The number of chunks
    */
    void SceneRenderer::setNumChunks(unsigned int numChunks)
    {
        _numChunks = numChunks;
    }

    /** Calculate the optimal number of chunks for the given dimensions
    * @param
    *   width The window width
    * @param
    *   height The window height
    */
    void SceneRenderer::calcOptimalChunks(unsigned int width, unsigned int height)
    {
        // Find the greatest common divisor
        // First use the binary method to simplify calculations
        unsigned int d = 1;
        bool canDivide = true;
        while(canDivide == true)
        {
            bool dW = (width % 2 == 0);
            bool dH = (height % 2 == 0);
            if(dW == true && dH == true)
            {
                width >>= 1;
                height >>= 1;
                d <<= 1;
            }
            else if(dW == true)
            {
                width >>= 1;
            }
            else if(dH == true)
            {
                height >>= 1;
            }
            else
            {
                canDivide = false;
            }
        }

        // We have pared down our values using binary method, so now we can find the GCD of this number
        canDivide = true;

        // Ensure width is the largest value
        if(height > width)
        {
            unsigned int t = width;
            width = height;
            height = t;
        }
        while(canDivide == true)
        {
            // Divide w by h
            unsigned int quotient = width / height;
            unsigned int remainder = width - (height * quotient);

            // Set height to width and remainder to height (then repeat)
            width = height;
            height = remainder;

            if(remainder == 0)
            {
                canDivide = false;
            }
        }

        // GCD is current width * d
        _numChunks = width * d;
    }

    /** Render the scene
    * @param
    *   width The viewport width
    * @param
    *   height The viewport height
    */
    void SceneRenderer::render(unsigned int width, unsigned int height)
    {
        // First, calculate the chunk dimensions
        getChunkDimensions(width, height);

        // Create the mutex
        _mutex = CreateMutex(NULL, FALSE, NULL);

        // Initialize the number of threads
        _numWorkers = _numChunks * _numChunks;
        _workers = new HANDLE[_numWorkers];
        _chunks = new ChunkData[_numWorkers];
        DWORD threadId;

		// Unset the rendering context before doing any work
		wglMakeCurrent(NULL, NULL);

        // Second, iterate over each section and render
        for(unsigned int i = 0; i < _numChunks; ++i)
        {
            for(unsigned int j = 0; j < _numChunks; ++j)
            {
                _chunks[i*_numChunks + j] = ChunkData(this, i, j);
                _workers[i*_numChunks + j] = CreateThread(
                                                          NULL,
                                                          0,
                                                          (LPTHREAD_START_ROUTINE) RenderWorker,
                                                          (LPVOID) &_chunks[i*_numChunks + j],
                                                          0,
                                                          &threadId);
                //renderChunk(i, j);
            }
        }
    }

    /** Calculate the chunk dimensions
    * @param
    *   tWidth The total width
    * @param
    *   tHeight The total height
    */
    void SceneRenderer::getChunkDimensions(unsigned int tWidth, unsigned int tHeight)
    {
        // Naively divide tWidth by numChunks
        _cWidth = tWidth / _numChunks;
        _cHeight = tHeight / _numChunks;
    }

    /** Render a chunk
    * @param
    *   startX The starting x index
    * @param
    *   startY The starting y index
    */
    void SceneRenderer::renderChunk(unsigned int startX, unsigned int startY)
    {
        float* pixels = new float[_cWidth*_cHeight*3];
        for(unsigned int i = 0; i < _cHeight; ++i)
        {
            for(unsigned int j = 0; j < _cWidth; ++j)
            {
                int pos = i * _cWidth + j;
                int ni = i + (_cHeight * startY);
                int nj = j + (_cWidth * startX);

                pixels[pos * 3] = (float)(nj) / float(_cWidth * _numChunks);
                pixels[pos * 3 + 1] = (float) (ni + nj) / float((_cWidth + _cHeight) * _numChunks);
                pixels[pos * 3 + 2] = (float) (nj) / float(_cHeight * _numChunks);
            }
        }
        float xpos = float(_cWidth * startX) / float((_cWidth * _numChunks) >> 1) - 1.0f;
        float ypos = (float)(_cHeight * startY) / float((_cHeight * _numChunks) >> 1) - 1.0f;

        // Get handle on mutex
		bool tryHandle = true;
		while(tryHandle == true)
		{
			HRESULT result = WaitForSingleObject(_mutex, 1000);

			if(result == WAIT_TIMEOUT || result == WAIT_FAILED)
			{
				Sleep(100);
			}
			else
			{
				// Create a context for this thread
				BOOL success = wglMakeCurrent(_hDC, _hRC);

				glRasterPos2f(xpos, ypos);
				glDrawPixels(_cWidth, _cHeight, GL_RGB, GL_FLOAT, pixels);
				glFlush();
				//glFinish();
				
				// Delete the rendering context
				wglMakeCurrent(NULL, NULL);

				// Release mutex
				ReleaseMutex(_mutex);

				// We are finished with this thread
				tryHandle = false;
			}
		}

        // Release the array of pixels
        delete[] pixels;
    }

    void SceneRenderer::setContext(HDC hDC, HGLRC hRC)
    {
        _hDC = hDC;
		_hRC = hRC;
    }

    DWORD WINAPI RenderWorker(LPVOID lpParam)
    {
        ChunkData* data = static_cast<ChunkData*>(lpParam);

        data->_sceneRenderer->renderChunk(data->_startX, data->_startY);

        return 0;
    }

}   // Namespace
