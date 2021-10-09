//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_WINDOW_TO_AWL_PARAMETERS_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_TO_AWL_PARAMETERS_HPP_INCLUDED

#include <sge/systems/original_window_fwd.hpp>
#include <awl/cursor/const_optional_object_ref_fwd.hpp>
#include <awl/visual/object_fwd.hpp>
#include <awl/window/parameters_fwd.hpp>

namespace sge::systems::impl::window
{

awl::window::parameters to_awl_parameters(
    awl::visual::object const &,
    awl::cursor::const_optional_object_ref const &,
    sge::systems::original_window const &);

}

#endif
