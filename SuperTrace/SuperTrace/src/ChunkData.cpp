#include "ChunkData.h"

namespace SuperTrace
{

    /** Default constructor
    */
    ChunkData::ChunkData()
    :   _sceneRenderer(0),
        _startX(0),
        _startY(0)
    {

    }

    /** Constructor
    */
    ChunkData::ChunkData(SceneRenderer* sceneRenderer, unsigned int startX, unsigned int startY)
    :   _sceneRenderer(sceneRenderer),
        _startX(startX),
        _startY(startY)
    {

    }

}
