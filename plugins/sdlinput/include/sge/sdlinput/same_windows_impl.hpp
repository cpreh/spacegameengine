//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_SAME_WINDOWS_IMPL_HPP_INCLUDED
#define SGE_SDLINPUT_SAME_WINDOWS_IMPL_HPP_INCLUDED

#include <awl/backends/sdl/window/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput
{

bool same_windows_impl(awl::backends::sdl::window::object const &, std::uint32_t);

}

#endif
