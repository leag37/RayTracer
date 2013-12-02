//*************************************************************************************************
// Title: SceneRenderer.h
// Author: Gael Huber
// Description: A basic class that takes care of chunking and rendering the scene data.
// Todo: Render scene based on SceneData object
//*************************************************************************************************
#ifndef __STSCENERENDERER_H__
#define __STSCENERENDERER_H__

#include <gl/gl.h>

namespace SuperTrace
{
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

        /** Render the scene
        * @param
        *   width The viewport width
        * @param
        *   height The viewport height
        */
        void render(unsigned int width, unsigned int height);

    private:
        /** Calculate the chunk dimensions
        * @param
        *   tWidth The total width
        * @param
        *   tHeight The total height
        * @param
        *   cWidth The chunk width
        * @param
        *   cHeight The chunk height
        */
        void getChunkDimensions(unsigned int tWidth, unsigned int tHeight, unsigned int &cWidth, unsigned int &cHeight);

        /** Render a chunk
        * @param
        *   cWidth The width of the chunk
        * @param
        *   cHeight The height of the chunk
        * @param
        *   startX The starting x index
        * @param
        *   startY The starting y index
        */
        void renderChunk(unsigned int cWidth, unsigned int cHeight, unsigned int startX, unsigned int startY);

    private:
        /** The number of chunks/jobs we want to split the render job into
        */
        unsigned int _numChunks;


    };

}   // Namespace

#endif // __STSCENERENDERER_H__
