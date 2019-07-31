//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PIXEL_FORMAT_COLOR_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_COLOR_HPP_INCLUDED

#include <sge/renderer/pixel_format/color_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace pixel_format
{

enum class color
{
	/**
	\brief A bit depth of 16 bits

	This means 5 bits for red and blue, and 5 or 6 bits for green.
	*/
	depth16,
	/**
	\brief A bit depth of 32 bits

	Red, blue and green have eigth bits with a possible unused channel for
	padding.
	*/
	depth32
};

}
}
}

#endif
