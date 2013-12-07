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
#include <Windows.h>
#include <gl/GL.h>

// TEMP
#include "Sphere.h"
// END TEMP

namespace SuperTrace
{
	DWORD WINAPI RenderWorker(LPVOID lpParam);
	DWORD WINAPI RenderProcessor(LPVOID lpParam);

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
		// Setup the camera
		float fovy = tan(60.0f * 0.5f * M_PI / 180.0f);
		//float fovy = 0.25f * M_PI;
		_camera = Camera(width, height, fovy);

		// First, calculate the chunk dimensions
		getChunkDimensions(width, height);

		// Initialize the pixel buffer data
		_pixelData = new float[width * height * 3];
		for(unsigned int i = 0; i < width * height * 3; ++i)
		{
			_pixelData[i] = 0.0f;
		}

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

		// Create thread for render processor
		CreateThread(	NULL,
						0,
						(LPTHREAD_START_ROUTINE) RenderProcessor,
						(LPVOID) this,
						0,
						&threadId);

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
				int pos = ((i * _cWidth) + j) * 3;
/*				int ni = i + (_cHeight * startY);
				int nj = j + (_cWidth * startX);

				pixels[pos * 3] = (float)(nj) / float(_cWidth * _numChunks);
				pixels[pos * 3 + 1] = (float) (ni + nj) / float((_cWidth + _cHeight) * _numChunks);
				pixels[pos * 3 + 2] = (float) (nj) / float(_cHeight * _numChunks);
				*/
				// Get the raster position
				unsigned int x = _cWidth * startX + j;
				unsigned int y = _cHeight * startY + i;

/*				pixels[pos] = float(startX) / float(_numChunks);
				pixels[pos + 1] = float(startY) / float(_numChunks);
				pixels[pos + 2] = float(startX + startY) / float(_numChunks + _numChunks);
				*/
				// Get the direction ray
				Ray ray = _camera.rasterToRay(x, y);
/*				pixels[pos] = (1.0f + ray.getDirection().getX()) * 0.5f;
				pixels[pos + 1] = (1.0f + ray.getDirection().getY()) * 0.5f;
				pixels[pos + 2] = 0.0f;
				*/
				// Create a sphere at (0, 0, -5)
				Sphere s = Sphere(Vector3(0.0f, 0.0f, -10.0f), 2.5f);
				Sphere s2 = Sphere(Vector3(4.0f, 0.0f, -12.0f), 1.5f);
				Sphere s3 = Sphere(Vector3(-4.0f, 2.0f, -10.0f), 2.0f);
				Sphere s4 = Sphere(Vector3(0.0f, 6.0f, -10.0f), 3.0f);
				bool intersect = false;
				bool tIntersect = false;
				if((tIntersect = s.testIntersect(ray)) == true)
				{
					intersect |= tIntersect;
					pixels[pos] = 1.0f;
					pixels[pos + 1] = 0.0f;
					pixels[pos + 2] = 0.0f;
				}
				if((tIntersect = s2.testIntersect(ray)) == true)
				{
					intersect |= tIntersect;
					pixels[pos] = 0.0f;
					pixels[pos + 1] = 0.0f;
					pixels[pos + 2] = 1.0f;
				}
				if((tIntersect = s3.testIntersect(ray)) == true)
				{
					intersect |= tIntersect;
					pixels[pos] = 1.0f;
					pixels[pos + 1] = 1.0f;
					pixels[pos + 2] = 0.0f;
				}
				if((tIntersect = s4.testIntersect(ray)) == true)
				{
					intersect |= tIntersect;
					pixels[pos] = 1.0f;
					pixels[pos + 1] = 0.0f;
					pixels[pos + 2] = 1.0f;
				}

				if(intersect == false)
				{
					pixels[pos] = 0.0f;
					pixels[pos + 1] = 1.0f;
					pixels[pos + 2] = 0.0f;
				}
			}
		}

		// Construct x and y position
		float initX = static_cast<float>(_cWidth * startX);
		float totalX = static_cast<float>(_cWidth * _numChunks) * 0.5f;
		float xpos = (initX / totalX) - 1.0f;

		float initY = static_cast<float>(_cHeight * startY);
		float totalY = static_cast<float>(_cHeight * _numChunks) * 0.5f;
		float ypos = (initY / totalY) - 1.0f;

		// Add to the list of completed blocks
		addRenderData(startX, startY, pixels);
	}

	// Add render data
	void SceneRenderer::addRenderData(unsigned int startX, unsigned int startY, float* renderData)
	{
		// Create pointer to render data
		RenderData* rd = new RenderData();
		rd->_startX = startX;
		rd->_startY = startY;
		rd->_pixelData = renderData;

		// First, acquire the job mutex
		bool tryEnqueue = true;
		while(tryEnqueue == true)
		{
			HRESULT result = WaitForSingleObject(_renderMutex, 1000);
			if(result == WAIT_TIMEOUT || result == WAIT_FAILED)
			{
				Sleep(100);
			}
			else
			{
				// Enqueue and release
				_renderQueue.push(rd);

				// Release the mutex
				ReleaseMutex(_renderMutex);

				// Exit loop
				tryEnqueue = false;
			}
		}
	} 

	// Try to get a piece of render data
	RenderData* SceneRenderer::getRenderData()
	{
		// The data to return
		RenderData* data = 0;

		// First, acquire the job mutex
		bool tryDequeue = true;
		while(tryDequeue == true)
		{
			// First, test for valid queue entry
			if(_renderQueue.size() == 0)
			{
				tryDequeue = false;
			}
			else
			{
				// There is a valid queue entry at lock attempt time
				HRESULT result = WaitForSingleObject(_renderMutex, 1000);
				if(result == WAIT_TIMEOUT || result == WAIT_FAILED)
				{
					Sleep(10);
				}
				else
				{
					// Now that we have acquired the lock, make sure we still have a valid queue entry

					if(_renderQueue.size() > 0)
					{
						data = _renderQueue.front();
						_renderQueue.pop();
						tryDequeue = false;
					}

					// Release the mutex
					ReleaseMutex(_renderMutex);
				}
			}
		}

		return data;
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

	// Acquire the render context
	void SceneRenderer::acquireContext()
	{
		// Create a context for this thread
		BOOL success = wglMakeCurrent(_hDC, _hRC);
	}

	// Draw a scene
	void SceneRenderer::drawToScreen(RenderData* data)
	{
		// Global position
		unsigned int width = _cWidth * _numChunks;
		unsigned int height = _cHeight * _numChunks;
		for(unsigned int i = 0; i < _cHeight; ++i)
		{
			for(unsigned int j = 0; j < _cWidth; ++j)
			{
				unsigned int pos = ((i * _cWidth) + j) * 3;
				unsigned int base = ((width * _cHeight) * data->_startY) + (width * i);
				unsigned int offset = (data->_startX * _cWidth) + j;

				// Inverse the base
				base = (width * height) - base - width;

				unsigned int p = (base + offset) * 3;
				_pixelData[p] = data->_pixelData[pos];
				_pixelData[p + 1] = data->_pixelData[pos + 1];
				_pixelData[p + 2] = data->_pixelData[pos + 2];
			}
		}

		// Tally the number of jobs we have left to handle
		decrementJobCount();

		glRasterPos2f(-1.0f, -1.0f);
		glDrawPixels(_cWidth * _numChunks, _cHeight * _numChunks, GL_RGB, GL_FLOAT, _pixelData);
		glFinish();
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
			else
			{
				Sleep(1000);
			}
		}

		return 0;
	}

	DWORD WINAPI RenderProcessor(LPVOID lpParam)
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
			}
			else
			{
				Sleep(1000);
			}
		}

		return 0;
	}

}   // Namespace
