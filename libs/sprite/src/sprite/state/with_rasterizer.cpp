//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/sprite/state/with_rasterizer.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/from.hpp>

sge::renderer::state::core::rasterizer::object_unique_ptr sge::sprite::state::with_rasterizer::make(
    sge::renderer::device::core_ref const _device,
    sge::sprite::state::with_rasterizer::optional_extra_parameters const &_enable_scissor_test)
{
  return _device.get().create_rasterizer_state(sge::renderer::state::core::rasterizer::parameters(
      sge::renderer::state::core::rasterizer::cull_mode::off,
      sge::renderer::state::core::rasterizer::fill_mode::solid,
      fcppt::optional::from(
          _enable_scissor_test,
          fcppt::const_(sge::renderer::state::core::rasterizer::enable_scissor_test{false}))));
}

void sge::sprite::state::with_rasterizer::set(
    sge::renderer::context::core &_context,
    fcppt::reference<sge::renderer::state::core::rasterizer::object const> const _state)
{
  _context.rasterizer_state(
      sge::renderer::state::core::rasterizer::const_optional_object_ref(_state));
}

void sge::sprite::state::with_rasterizer::unset(sge::renderer::context::core &_context)
{
  _context.rasterizer_state(sge::renderer::state::core::rasterizer::const_optional_object_ref());
}
