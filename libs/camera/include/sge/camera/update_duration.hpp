//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_UPDATE_DURATION_HPP_INCLUDED
#define SGE_CAMERA_UPDATE_DURATION_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>

namespace sge::camera
{

using update_duration = std::chrono::duration<sge::renderer::scalar>;

}

#endif
