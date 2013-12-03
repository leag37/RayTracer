#include "ChunkData.h"

namespace SuperTrace
{

    /** Default constructor
    */
    ChunkData::ChunkData()
    :   _startX(0),
        _startY(0)
    {

    }

    /** Constructor
    */
    ChunkData::ChunkData(unsigned int startX, unsigned int startY)
	:   _startX(startX),
        _startY(startY)
    {

    }

}
