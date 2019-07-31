//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_FOCUS_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_INPUT_FOCUS_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/input/focus/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace input
{
namespace focus
{

typedef
fcppt::unique_ptr<
	sge::input::focus::object
>
object_unique_ptr;

}
}
}

#endif
