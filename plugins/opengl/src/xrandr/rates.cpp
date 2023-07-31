//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/const_configuration_ref.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/rates.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::rates::rates(
    sge::opengl::xrandr::const_configuration_ref const _config,
    sge::opengl::xrandr::mode_index const _mode)
    : size_{0}, rates_{::XRRConfigRates(_config.get().get(), _mode.get(), &size_)}
{
}

sge::opengl::xrandr::rates::iterator sge::opengl::xrandr::rates::begin() const { return rates_; }

sge::opengl::xrandr::rates::iterator sge::opengl::xrandr::rates::end() const
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  return rates_ + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
         size_;

FCPPT_PP_POP_WARNING
}

sge::opengl::xrandr::rates::size_type sge::opengl::xrandr::rates::size() const
{
  return fcppt::cast::to_unsigned(size_);
}
