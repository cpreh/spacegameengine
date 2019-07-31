//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_IS_HIERARCHY_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_IS_HIERARCHY_HPP_INCLUDED

#include <sge/x11input/event/type_c.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Value
>
struct is_hierarchy
:
std::is_same<
	Value,
	sge::x11input::event::type_c<
		XI_HierarchyChanged
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
