//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_OPTIONAL_STATE_FWD_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_OPTIONAL_STATE_FWD_HPP_INCLUDED

#include <sge/wlinput/focus/state_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

using
optional_state
=
fcppt::optional::object<
	sge::wlinput::focus::state
>;

}
}
}

#endif
