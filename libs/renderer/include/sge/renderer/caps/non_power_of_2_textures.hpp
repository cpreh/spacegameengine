//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CAPS_NON_POWER_OF_2_TEXTURES_HPP_INCLUDED
#define SGE_RENDERER_CAPS_NON_POWER_OF_2_TEXTURES_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::renderer::caps
{

/**
\brief A strong typedef for a bool telling if non power of 2 textures are supported
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	bool,
	non_power_of_2_textures
);

}

#endif
