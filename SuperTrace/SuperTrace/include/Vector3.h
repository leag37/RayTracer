// Define a 3D vector
// Author: Gael Huber
#ifndef __STVECTOR3_H__
#define __STVECTOR3_H__

namespace SuperTrace
{
    /** \addtogroup Math
    *   @{
    */

    class Vector3
    {
    public:
        /** Default constructor
        */
        Vector3();

        /** Constructor
        * @param
        *   x The x coordinate
        * @param
        *   y The y coordinate
        * @param
        *   z The z coordinate
        */
        Vector3(float x, float y, float z);

        /** Addition operator
        * @param
        *   vec The vector to add
        * @return
        *   Vector3 The sum of two vectors
        */
        Vector3 operator+(const Vector3& vec);

        // Get the x value
        float getX() const;
        float getY() const;
        float getZ() const;
        float operator[](int i) const;

    private:
        // The definition of the data
        union
        {
            struct
            {
                float x;
                float y;
                float z;
            } v;
            float f[3];
        };
    };

    /** @} */

}   // Namespace

#endif // __STVECTOR3_H__
