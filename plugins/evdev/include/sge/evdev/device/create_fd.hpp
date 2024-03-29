//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_DEVICE_CREATE_FD_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_CREATE_FD_HPP_INCLUDED

#include <sge/evdev/device/optional_fd_unique_ptr.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::device
{

sge::evdev::device::optional_fd_unique_ptr create_fd(
    fcppt::log::object &, // NOLINT(google-runtime-references)
    std::filesystem::path const &);

}

#endif
