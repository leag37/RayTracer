//*************************************************************************************************
// Title: SceneRenderer.cpp
// Author: Gael Huber
// Description: Implementation file for SceneRenderer
//*************************************************************************************************
#include "SceneRenderer.h"
#include "ChunkData.h"
#include "RenderData.h"
#include "Camera.h"
#include "STMath.h"
#include "Scene.h"
#include "Color.h"
#include <Windows.h>
#include <gl/GL.h>

// TEMP
#include "Sphere.h"
// END TEMP

namespace SuperTrace
{
	DWORD WINAPI TraceWorker(LPVOID lpParam);
	DWORD WINAPI RenderWorker(LPVOID lpParam);
	CRITICAL_SECTION cs;

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
		_scene = new Scene();
		_scene->createScene();

		// Setup the camera
		float fovy = tan(60.0f * 0.5f * M_PI / 180.0f);
		Camera* camera = new Camera(width, height, fovy);
		_scene->setCamera(camera);

		// First, calculate the chunk dimensions
		getChunkDimensions(width, height);

		// Initialize the pixel buffer data
		_pixelData = new float[width * height * 3];
		for(unsigned int i = 0; i < width * height * 3; ++i)
		{
			_pixelData[i] = 0.0f;
		}

		// Create the mutex
		InitializeCriticalSectionAndSpinCount(&_renderMutex, 0x00000400);
		InitializeCriticalSectionAndSpinCount(&_jobMutex, 0x00000400);
		InitializeCriticalSectionAndSpinCount(&cs, 0x00000400);

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
										(LPTHREAD_START_ROUTINE) TraceWorker,
										(LPVOID) this,
										0,
										&threadId);
		}

		// Create thread for render processor
		CreateThread(	NULL,
						0,
						(LPTHREAD_START_ROUTINE) RenderWorker,
						(LPVOID) this,
						0,
						&threadId);
						
		// Second, iterate over each section and render
		for(unsigned int i = 0; i < _numChunks; ++i)
		{
			for(unsigned int j = 0; j < _numChunks; ++j)
			{
				// Ask enqueue object
				addTraceableChunk(new ChunkData(i, j));
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
	void SceneRenderer::traceChunk(unsigned int startX, unsigned int startY)
	{
		//float* pixels = new float[_cWidth*_cHeight*3];
		unsigned int width = _cWidth * _numChunks;
		unsigned int height = _cHeight * _numChunks;

		bool test = false;
		
		for(unsigned int i = 0; i < _cHeight; ++i)
		{
			// Calculate base array position
			unsigned int base = ((width * _cHeight) * startY) + (width * i);
			// Inverse the base
			base = (width * height) - base - width;
	
			// Calculate rasterized y value
			unsigned int y = _cHeight * startY + i;

			for(unsigned int j = 0; j < _cWidth; ++j)
			{
				int pos = ((i * _cWidth) + j) * 3;

				// Get the raster position
				unsigned int x = _cWidth * startX + j;
				
				// Get a color from the scene
				Color color = _scene->trace(x, y);

/*				if(color.r == float(float(x)/1024.0f) || color.g == float(float(y)/768.0f))
				{
					if(startX > 8 && startX < 24 && startY > 8 && startY < 24)
					{
						int a =0;
						_scene->trace(x, y);
					}
					test = true;
				}*/

				// Calculate offset from width
				unsigned int offset = (startX * _cWidth) + j;
				unsigned int p = (base + offset) * 3;
				_pixelData[p] = color.r;
				_pixelData[p + 1] = color.g;
				_pixelData[p + 2] = color.b;
			}
		}

		if(test == true && startX > 8 && startX < 24 && startY > 8 && startY < 24)
		{
			int a = 0;
		}

		// Construct x and y position
/*		float initX = static_cast<float>(_cWidth * startX);
		float totalX = static_cast<float>(_cWidth * _numChunks) * 0.5f;
		float xpos = (initX / totalX) - 1.0f;

		float initY = static_cast<float>(_cHeight * startY);
		float totalY = static_cast<float>(_cHeight * _numChunks) * 0.5f;
		float ypos = (initY / totalY) - 1.0f;
		*/
		// Add to the list of completed blocks
		addRenderData(startX, startY, 0);
	}

	// Add render data
	void SceneRenderer::addRenderData(unsigned int startX, unsigned int startY, float* renderData)
	{
		// First, acquire the job mutex
		EnterCriticalSection(&_renderMutex);

		// Create pointer to render data
		RenderData* rd = new RenderData();
		rd->_startX = startX;
		rd->_startY = startY;
		rd->_pixelData = renderData;
			
		// Enqueue and release
		_renderQueue.push(rd);

		// Release the mutex
		LeaveCriticalSection(&_renderMutex);
	} 

	// Try to get a piece of render data
	RenderData* SceneRenderer::getRenderData()
	{
		// The data to return
		RenderData* data = 0;

		// There is a valid queue entry at lock attempt time
		EnterCriticalSection(&_renderMutex);
		
		// Now that we have acquired the lock, make sure we still have a valid queue entry
		if(_renderQueue.size() > 0)
		{
			data = _renderQueue.front();
			_renderQueue.pop();
		}

		// Release the mutex
		LeaveCriticalSection(&_renderMutex);

		return data;
	}

	// Enqueue a chunk
	void SceneRenderer::addTraceableChunk(ChunkData* chunk)
	{
		// First, acquire the job mutex
		EnterCriticalSection(&_jobMutex);

		// Enqueue and release
		_chunkQueue.push(chunk);

		// Release the mutex
		LeaveCriticalSection(&_jobMutex);
	}

	// Dequeue a chunk
	ChunkData* SceneRenderer::getTraceableChunk()
	{

		// The data to return
		ChunkData* data = 0;

		EnterCriticalSection(&_jobMutex);

		// Now that we have acquired the lock, make sure we still have a valid queue entry
		if(_chunkQueue.size() > 0)
		{
			data = _chunkQueue.front();
			_chunkQueue.pop();
		}

		// Release the mutex
		LeaveCriticalSection(&_jobMutex);

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

	// Acquire the render context
	void SceneRenderer::acquireContext()
	{
		// Create a context for this thread
		BOOL success = wglMakeCurrent(_hDC, _hRC);
	}

	// Draw a scene
	void SceneRenderer::drawToScreen(RenderData* data)
	{
		// Tally the number of jobs we have left to handle
		decrementJobCount();

		glRasterPos2f(-1.0f, -1.0f);
		glDrawPixels(_cWidth * _numChunks, _cHeight * _numChunks, GL_RGB, GL_FLOAT, _pixelData);
		glFinish();
	}

	DWORD WINAPI TraceWorker(LPVOID lpParam)
	{
		// Get the scene
		SceneRenderer* sceneRenderer = static_cast<SceneRenderer*>(lpParam);
		
		// While the scene is not complete
		while(sceneRenderer->getIsSceneComplete() == false)
		{
			//EnterCriticalSection(&cs);

			// Get a chunk from the queue
			ChunkData* data = sceneRenderer->getTraceableChunk();

			// If the chunk is valid, render otherwise skip
			if(data != 0)
			{
				sceneRenderer->traceChunk(data->_startX, data->_startY);

				// Delete the data
				delete data;
				data = 0;
			}
			else
			{
				Sleep(1000);
			}

			//LeaveCriticalSection(&cs);
		}

		return 0;
	}

	DWORD WINAPI RenderWorker(LPVOID lpParam)
	{
		// Get context
		SceneRenderer* sceneRenderer = static_cast<SceneRenderer*>(lpParam);

		// Acquire gl context for this thread
		sceneRenderer->acquireContext();
		
		// While the scene is not complete
		while(sceneRenderer->getIsSceneComplete() == false)
		{
			// Get a chunk from the queue
			RenderData* data = sceneRenderer->getRenderData();

			// If the chunk is valid, render otherwise skip
			if(data != 0)
			{
				sceneRenderer->drawToScreen(data);
				delete data;
				data = 0;
			}
			else
			{
				Sleep(1000);
			}
		}

		return 0;
	}

}   // Namespace
