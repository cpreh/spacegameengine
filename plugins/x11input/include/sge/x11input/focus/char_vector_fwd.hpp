//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_FOCUS_CHAR_VECTOR_FWD_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_CHAR_VECTOR_FWD_HPP_INCLUDED

#include <sge/input/focus/char_type.hpp>
#include <fcppt/container/raw_vector/object_fwd.hpp>


namespace sge
{
namespace x11input
{
namespace focus
{

typedef
fcppt::container::raw_vector::object<
	sge::input::focus::char_type
>
char_vector;

}
}
}

#endif
