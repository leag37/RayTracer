//

#ifndef __STCHUNKDATA_H__
#define __STCHUNKDATA_H__

namespace SuperTrace
{
    class ChunkData
    {
    public:
        /** Default constructor
        */
        ChunkData();

        /** Constructor
        */
        ChunkData(unsigned int startX, unsigned int startY);

        unsigned int _startX;
        unsigned int _startY;
    };

}

#endif // __STCHUNKDATA_H__
