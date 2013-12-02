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

}   // Namespace
