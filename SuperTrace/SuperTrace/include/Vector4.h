//*************************************************************************************************
// Title: Vector4.h
// Author: Gael Huber
// Description: Define a 3D vector
//*************************************************************************************************
#ifndef __STVECTOR4_H__
#define __STVECTOR4_H__

namespace SuperTrace
{
	/** \addtogroup Math
	*   @{
	*/

	class Vector4
	{
	public:
		/** Default constructor
		*/
		Vector4();

		/** Constructor
		* @param
		*   x The x coordinate
		* @param
		*   y The y coordinate
		* @param
		*   z The z coordinate
		* @param
		*	w The w coordinate
		*/
		Vector4(float x, float y, float z, float w);

		/** Constructor
		* @param
		*	v An array of three floats
		*/
		Vector4(float* v);

		/** Copy constructor
		*/
		Vector4(const Vector4& v);

		/** Destructor
		*/
		~Vector4();

		/** Assignment operator
		*/
		Vector4& operator=(const Vector4& v);

		/** Equivalence operator
		*/
		bool operator==(const Vector4& v) const;

		/** Non equivalence operator
		*/
		bool operator!=(const Vector4& v) const;

		/** Addition operator
		* @param
		*   vec The vector to add
		* @return
		*   Vector4 The sum of two vectors
		*/
		Vector4 operator+(const Vector4& v) const;

		/** Addition operator
		* @param
		*   vec The vector to add
		* @return
		*   Vector4& The sum of two vectors
		*/
		Vector4& operator+=(const Vector4& v);

		/** Subtraction operator
		* @param
		*   vec The vector to subtract
		* @return
		*   Vector4 The difference of two vectors
		*/
		Vector4 operator-(const Vector4& v) const;

		/** Subtraction operator
		* @param
		*   vec The vector to subtract
		* @return
		*   Vector4& The difference of two vectors
		*/
		Vector4& operator-=(const Vector4& v);

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4 The scaled vector
		*/
		Vector4 operator*(const Vector4& scale) const;

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4 The scaled vector
		*/
		Vector4 operator*(float scale) const;

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @param
		*	vec The vector to scale
		* @return
		*	Vector4 The scaled vector
		*/
		friend Vector4 operator*(float scale, const Vector4& v);

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4& The scaled vector
		*/
		Vector4& operator*=(float scale);

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4 The scaled vector
		*/
		Vector4 operator/(float scale) const;

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4& The scaled vector
		*/
		Vector4& operator/=(float scale);

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4 The scaled vector
		*/
		Vector4 operator/(const Vector4& scale) const;

		/** Scale operator
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4& The scaled vector
		*/
		Vector4& operator/=(const Vector4& scale);

		/** Scale operator
		* @param
		*	base The base value (identical across vector)
		* @param
		*	scale The value by which to scale
		* @return
		*	Vector4 The scaled vector
		*/
		friend Vector4 operator/(float base, const Vector4& scale);

		/** Dot product
		* @param
		*	v The vector with which to take the dot product
		* @return 
		*	float The dot product
		*/
		float dot(const Vector4& v) const;

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
		*	Vector4 A normalized copy of this vector
		*/
		Vector4 normal() const;

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

		/** Get the w value
		* @return
		*	float The w value of the vector
		*/
		float getW() const;

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
				float _w;
			};
			float _f[4];
		};
	};

	/** @} */

}   // Namespace

#endif // __STVECTOR4_H__
