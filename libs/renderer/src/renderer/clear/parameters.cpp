//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/clear/back_buffer_value.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/clear/optional_back_buffer.hpp>
#include <sge/renderer/clear/optional_depth_buffer.hpp>
#include <sge/renderer/clear/optional_stencil_buffer.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/clear/stencil_buffer_value.hpp>

sge::renderer::clear::parameters::parameters() : back_buffer_(), depth_buffer_(), stencil_buffer_()
{
}

sge::renderer::clear::parameters &sge::renderer::clear::parameters::back_buffer(
    sge::renderer::clear::back_buffer_value const &_back_buffer)
{
  back_buffer_ = sge::renderer::clear::optional_back_buffer(_back_buffer);

  return *this;
}

sge::renderer::clear::parameters &sge::renderer::clear::parameters::depth_buffer(
    sge::renderer::clear::depth_buffer_value const _depth_buffer)
{
  depth_buffer_ = sge::renderer::clear::optional_depth_buffer(_depth_buffer);

  return *this;
}

sge::renderer::clear::parameters &sge::renderer::clear::parameters::stencil_buffer(
    sge::renderer::clear::stencil_buffer_value const _stencil_buffer)
{
  stencil_buffer_ = sge::renderer::clear::optional_stencil_buffer(_stencil_buffer);

  return *this;
}

sge::renderer::clear::optional_back_buffer const &
sge::renderer::clear::parameters::back_buffer() const
{
  return back_buffer_;
}

sge::renderer::clear::optional_depth_buffer const &
sge::renderer::clear::parameters::depth_buffer() const
{
  return depth_buffer_;
}

sge::renderer::clear::optional_stencil_buffer const &
sge::renderer::clear::parameters::stencil_buffer() const
{
  return stencil_buffer_;
}
