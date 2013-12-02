//

#ifndef __STCHUNKDATA_H__
#define __STCHUNKDATA_H__

namespace SuperTrace
{
    class SceneRenderer;

    class ChunkData
    {
    public:
        /** Default constructor
        */
        ChunkData();

        /** Constructor
        */
        ChunkData(SceneRenderer* sceneRenderer, unsigned int startX, unsigned int startY);


        unsigned int startX;
        unsigned int startY;
    };

}

#endif // __STCHUNKDATA_H__
