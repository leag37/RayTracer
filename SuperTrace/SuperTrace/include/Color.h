//*************************************************************************************************
// Title: Color.h
// Author: Gael Huber
// Description: Defines a simple color
//*************************************************************************************************
#ifndef __STCOLOR_H__
#define __STCOLOR_H__

namespace SuperTrace
{
	/** \addtogroup Scene
	*	@{
	*/

	class Color
	{
	public:
		Color()
			:	r(0.0f), g(0.0f), b(0.0f)
		{ }

		Color(float inR, float inG, float inB)
			:	r(inR), g(inG), b(inB)
		{ }

		float r;
		float g;
		float b;
	};

	/** @} */

}	// Namespace

#endif // __STCOLOR_H__