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

        SceneRenderer* _sceneRenderer;
        unsigned int _startX;
        unsigned int _startY;
    };

}

#endif // __STCHUNKDATA_H__
