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

		/** Constructor
		* @param
		*	v An array of three floats
		*/
		Vector3(float* v);

		/** Copy constructor
		*/
		Vector3(const Vector3& v);

		/** Destructor
		*/
		~Vector3();

		/** Assignment operator
		*/
		Vector3& operator=(const Vector3& v);

		/** Equivalence operator
		*/
		bool operator==(const Vector3& v) const;

		/** Non equivalence operator
		*/
		bool operator!=(const Vector3& v) const;

        /** Addition operator
        * @param
        *   vec The vector to add
        * @return
        *   Vector3 The sum of two vectors
        */
        Vector3 operator+(const Vector3& v) const;

		/** Addition operator
        * @param
        *   vec The vector to add
        * @return
        *   Vector3& The sum of two vectors
        */
        Vector3& operator+=(const Vector3& v);

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector3 The scaled vector
		*/
		Vector3 operator*(float scale) const;

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @param
		*	vec The vector to scale
		* @return
		*	Vector3 The scaled vector
		*/
		friend Vector3 operator*(float scale, const Vector3& v);

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector3& The scaled vector
		*/
		Vector3& operator*=(float scale);

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector3 The scaled vector
		*/
		Vector3 operator/(float scale) const;

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector3& The scaled vector
		*/
		Vector3& operator/=(float scale);

		/** Dot product
		* @param
		*	v The vector with which to take the dot product
		* @return 
		*	float The dot product
		*/
		float dot(const Vector3& v) const;

		/** Cross product
		* @param
		*	v The vector with which to cross
		* @return
		*	Vector3 The cross product
		*/
		Vector3 cross(const Vector3& v) const;

		/** The squared length of the vector
		* @return
		*	float The squared length of the vector
		*/
		float lengthSqr() const;

		/** The length of the vector
		* @return
		*	float The length of the vector
		*/
		float length() const;

		/** Normalize the vector
		*/
		void normalize();

		/** Return a normalized version of the vector
		* @return
		*	Vector3 A normalized copy of this vector
		*/
		Vector3 normal() const;

        /** Get the x value
		* @return
		*	float The x value of the vector
		*/
		float getX() const;

		/** Get the y value
		* @return
		*	float The y value of the vector
		*/
        float getY() const;

		/** Get the z value
		* @return
		*	float The z value of the vector
		*/
        float getZ() const;

		/** Get a value from the vector by index
		* @param
		*	index The index of the desired value, in the order 0=>x, 1=>y, 2=>z
		* @return
		*	float The value corresponding to the specified index
		*/
        float operator[](unsigned int i) const;

		/** Get a value from the vector by index
		* @param
		*	index The index of the desired value, in the order 0=>x, 1=>y, 2=>z
		* @return
		*	float The value corresponding to the specified index
		*/
        float operator[](int i) const;

    private:
        // The definition of the data
        union
        {
            struct
            {
                float _x;
                float _y;
                float _z;
            };
            float _f[3];
        };
    };

    /** @} */

}   // Namespace

#endif // __STVECTOR3_H__
