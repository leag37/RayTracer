//*************************************************************************************************
// Title: SceneRenderer.cpp
// Author: Gael Huber
// Description: Implementation file for SceneRenderer
//*************************************************************************************************
#include "SceneRenderer.h"

namespace SuperTrace
{
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

    /** Render the scene
    * @param
    *   width The viewport width
    * @param
    *   height The viewport height
    */
    void SceneRenderer::render(unsigned int width, unsigned int height)
    {
        // First, calculate the chunk dimensions
        unsigned int cWidth = 0, cHeight = 0;
        getChunkDimensions(width, height, cWidth, cHeight);

        // Second, iterate over each section and render
        for(unsigned int i = 0; i < _numChunks; ++i)
        {
            for(unsigned int j = 0; j < _numChunks; ++j)
            {
                renderChunk(cWidth, cHeight, i, j);
            }
        }
    }

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
    void SceneRenderer::getChunkDimensions(unsigned int tWidth, unsigned int tHeight, unsigned int &cWidth, unsigned int &cHeight)
    {
        // Naively divide tWidth by numChunks
        cWidth = tWidth / _numChunks;
        cHeight = tHeight / _numChunks;
    }

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
    void SceneRenderer::renderChunk(unsigned int cWidth, unsigned int cHeight, unsigned int startX, unsigned int startY)
    {
        float* pixels = new float[cWidth*cHeight*3];
        for(unsigned int i = 0; i < cHeight; ++i)
        {
            for(unsigned int j = 0; j < cWidth; ++j)
            {
                int pos = i * cWidth + j;
                int ni = i + (cHeight * startY);
                int nj = j + (cWidth * startX);

                pixels[pos * 3] = (float)(nj) / float(cWidth * _numChunks);
                pixels[pos * 3 + 1] = (float) (ni + nj) / float((cWidth + cHeight) * _numChunks);
                pixels[pos * 3 + 2] = (float) (nj) / float(cHeight * _numChunks);
            }


        }
        float xpos = float(cWidth * startX) / float((cWidth * _numChunks) >> 1) - 1.0f;
        float ypos = (float)(cHeight * startY) / float((cHeight * _numChunks) >> 1) - 1.0f;
        glRasterPos2f(xpos, ypos);
        glDrawPixels(cWidth, cHeight, GL_RGB, GL_FLOAT, pixels);
        glFlush();
    }

}   // Namespace
