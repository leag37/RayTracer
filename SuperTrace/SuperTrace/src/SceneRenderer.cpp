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
        _renderMutex = CreateMutex(NULL, FALSE, NULL);
		_jobMutex = CreateMutex(NULL, FALSE, NULL);

        // Initialize the number of threads
        _numWorkers = 100;
        _workers = new HANDLE[_numWorkers];
		_numJobs = _numChunks * _numChunks;
        DWORD threadId;

		// Unset the rendering context before doing any work
		wglMakeCurrent(NULL, NULL);

		// Start the workers
		for(unsigned int i = 0; i < _numWorkers; ++i)
		{
			_workers[i] = CreateThread(	NULL,
                                        0,
                                        (LPTHREAD_START_ROUTINE) RenderWorker,
                                        (LPVOID) this,
                                        0,
                                        &threadId);
		}

        // Second, iterate over each section and render
        for(unsigned int i = 0; i < _numChunks; ++i)
        {
            for(unsigned int j = 0; j < _numChunks; ++j)
            {
				// Ask enqueue object
				enqueue(new ChunkData(i, j));
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
			HRESULT result = WaitForSingleObject(_renderMutex, 1000);

			if(result == WAIT_TIMEOUT || result == WAIT_FAILED)
			{
				Sleep(10);
			}
			else
			{
				// Tally the number of jobs we have left to handle
				decrementJobCount();

				// Create a context for this thread
				BOOL success = wglMakeCurrent(_hDC, _hRC);

				glRasterPos2f(xpos, ypos);
				glDrawPixels(_cWidth, _cHeight, GL_RGB, GL_FLOAT, pixels);
				glFlush();
				
				// Delete the rendering context
				wglMakeCurrent(NULL, NULL);

				// Release mutex
				ReleaseMutex(_renderMutex);

				// We are finished with this thread
				tryHandle = false;
			}
		}

        // Release the array of pixels
        delete[] pixels;
    }

	// Enqueue a chunk
	void SceneRenderer::enqueue(ChunkData* chunk)
	{
		// First, acquire the job mutex
		bool tryEnqueue = true;
		while(tryEnqueue == true)
		{
			HRESULT result = WaitForSingleObject(_jobMutex, 1000);
			if(result == WAIT_TIMEOUT || result == WAIT_FAILED)
			{
				Sleep(100);
			}
			else
			{
				// Enqueue and release
				_queue.push(chunk);

				// Release the mutex
				ReleaseMutex(_jobMutex);

				// Exit loop
				tryEnqueue = false;
			}
		}
	}

	// Dequeue a chunk
	ChunkData* SceneRenderer::dequeue()
	{
		// The data to return
		ChunkData* data = 0;

		// First, acquire the job mutex
		bool tryDequeue = true;
		while(tryDequeue == true)
		{
			// First, test for valid queue entry
			if(_queue.size() == 0)
			{
				tryDequeue = false;
			}
			else
			{
				// There is a valid queue entry at lock attempt time
				HRESULT result = WaitForSingleObject(_jobMutex, 1000);
				if(result == WAIT_TIMEOUT || result == WAIT_FAILED)
				{
					Sleep(10);
				}
				else
				{
					// Now that we have acquired the lock, make sure we still have a valid queue entry

					if(_queue.size() > 0)
					{
						data = _queue.front();
						_queue.pop();
						tryDequeue = false;
					}

					// Release the mutex
					ReleaseMutex(_jobMutex);
				}
			}
		}

		return data;
	}


    void SceneRenderer::setContext(HDC hDC, HGLRC hRC)
    {
        _hDC = hDC;
		_hRC = hRC;
    }

	// Decrement the number of jobs left to handle
	void SceneRenderer::decrementJobCount()
	{
		--_numJobs;
	}

	/** Get isSceneComplete
	*/
	bool SceneRenderer::getIsSceneComplete()
	{
		return _numJobs == 0;
	}

    DWORD WINAPI RenderWorker(LPVOID lpParam)
    {
		// Get context
		SceneRenderer* sceneRenderer = static_cast<SceneRenderer*>(lpParam);
		
		// While the scene is not complete
		while(sceneRenderer->getIsSceneComplete() == false)
		{
			// Get a chunk from the queue
			ChunkData* data = sceneRenderer->dequeue();

			// If the chunk is valid, render otherwise skip
			if(data != 0)
			{
				sceneRenderer->renderChunk(data->_startX, data->_startY);

				// Delete the data
				delete data;
			}
		}

        return 0;
    }

}   // Namespace
