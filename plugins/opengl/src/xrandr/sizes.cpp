//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/const_configuration_ref.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/sizes.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::sizes::sizes(sge::opengl::xrandr::const_configuration_ref const _config)
    : size_{0}, sizes_{::XRRConfigSizes(_config.get().get(), &size_)}
{
}

sge::opengl::xrandr::sizes::iterator sge::opengl::xrandr::sizes::begin() const { return sizes_; }

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

sge::opengl::xrandr::sizes::iterator sge::opengl::xrandr::sizes::end() const
{
  return sizes_ + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
         size_;
}

XRRScreenSize const &
sge::opengl::xrandr::sizes::operator[](sge::opengl::xrandr::mode_index const _index) const
{
  return *(this->begin() + _index.get());
}

FCPPT_PP_POP_WARNING

sge::opengl::xrandr::mode_index sge::opengl::xrandr::sizes::size() const
{
  return sge::opengl::xrandr::mode_index{size_};
}
