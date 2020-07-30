//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_JOYPAD_INIT_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_INIT_HPP_INCLUDED

#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sdlinput
{
namespace joypad
{

std::vector<
	sge::sdlinput::joypad::shared_ptr
>
init(
	sge::window::object_ref,
	fcppt::log::object & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}
}

#endif
