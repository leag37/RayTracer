//*************************************************************************************************
// Title: SceneRenderer.h
// Author: Gael Huber
// Description: A basic class that takes care of chunking and rendering the scene data.
// Todo: Render scene based on SceneData object
//*************************************************************************************************
#ifndef __STSCENERENDERER_H__
#define __STSCENERENDERER_H__

#include <windows.h>
#include <queue>
#include "Camera.h"

namespace SuperTrace
{
	/** \addtogroup Scene
	*	@{
	*/

	class ChunkData;
	class RenderData;

	class SceneRenderer
	{
	public:
		/** Default constructor
		*/
		SceneRenderer();

		/** Destructor
		*/
		~SceneRenderer();

		/** Set the number of chunks
		* @param
		*   numChunks The number of chunks
		*/
		void setNumChunks(unsigned int numChunks);

		/** Calculate the optimal number of chunks for the given dimensions
		* @param
		*   width The window width
		* @param
		*   height The window height
		*/
		void calcOptimalChunks(unsigned int width, unsigned int height);

		/** Render the scene
		* @param
		*   width The viewport width
		* @param
		*   height The viewport height
		*/
		void render(unsigned int width, unsigned int height);

		/** Render a chunk
		* @param
		*   startX The starting x index
		* @param
		*   startY The starting y index
		*/
		void renderChunk(unsigned int startX, unsigned int startY);

		/** Set context
		*/
		void setContext(HDC hDC, HGLRC hRC);

		/** Get isSceneComplete
		*/
		bool getIsSceneComplete();

		// Enqueue a chunk
		void enqueue(ChunkData* chunk);

		// Dequeue a chunk
		ChunkData* dequeue();

		// Get a piece of render data
		RenderData* getRenderData();

		// Acquire the render context
		void acquireContext();

		// Draw a scene
		void drawToScreen(RenderData* data);

	private:
		/** Calculate the chunk dimensions
		* @param
		*   tWidth The total width
		* @param
		*   tHeight The total height
		*/
		void getChunkDimensions(unsigned int tWidth, unsigned int tHeight);

		// Decrement the number of jobs left to handle
		void decrementJobCount();

		// Add to the render data list
		void addRenderData(unsigned int startX, unsigned int startY, float* renderData);

	private:
		/** The number of chunks/jobs we want to split the render job into
		*/
		unsigned int _numChunks;

		/** The number of threads we will launch
		*/
		unsigned int _numWorkers;

		/** Worker threads
		*/
		HANDLE* _workers;

		/** Mutex
		*/
		HANDLE _renderMutex;

		/** Job mutex
		*/
		HANDLE _jobMutex;

		/** Number of jobs to handle total
		*/
		unsigned int _numJobs;

		/** Array of chunk data
		*/
		std::queue<ChunkData*> _queue;

		/** Array of render data
		*/
		std::queue<RenderData*> _renderQueue;

		/** Render context values
		*/
		HDC _hDC;
		HGLRC _hRC;

		/** The chunk width
		*/
		unsigned int _cWidth;

		/** The chunk height
		*/
		unsigned int _cHeight;

		/** Global buffer
		*/
		float* _pixelData;

		/** Camera
		*/
		Camera _camera;
	};

	/** @} */

}   // Namespace

#endif // __STSCENERENDERER_H__
