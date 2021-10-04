//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_FIRST_PERSON_ACTION_LEFT_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_ACTION_LEFT_HPP_INCLUDED

#include <sge/input/key/optional_code.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::camera::first_person::action
{

/**
\brief The (optional) key code belonging to the action "go left"
\ingroup sgecamera
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::input::key::optional_code,
	left
);

}

#endif
