//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_SPHERICAL_ACTION_DECREASE_RADIUS_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_ACTION_DECREASE_RADIUS_HPP_INCLUDED

#include <sge/input/key/optional_code.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{
namespace action
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::input::key::optional_code,
	decrease_radius
);

}
}
}
}

#endif
