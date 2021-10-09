//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/base.hpp>
#include <sge/camera/const_base_ref.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/scenic/grid/object.hpp>
#include <sge/scenic/grid/orientation.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/enum/array_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/optional/maybe_void.hpp>

namespace
{

using inner_array = fcppt::array::object<fcppt::math::size_type, 3>;

fcppt::enum_::array<sge::scenic::grid::orientation, inner_array> const axis_mappings{
    inner_array{// xz
                0U,
                2U,
                1U},
    inner_array{// xy
                0U,
                1U,
                2U},
    inner_array{// yz
                2U,
                0U,
                1U}};

sge::renderer::vector3 permute_vector_according_to_orientation(
    sge::scenic::grid::orientation const _orientation, sge::renderer::vector3 const &_input)
{
  return sge::renderer::vector3(
      _input.get_unsafe(fcppt::array::get<0>(axis_mappings[_orientation])),
      _input.get_unsafe(fcppt::array::get<1>(axis_mappings[_orientation])),
      _input.get_unsafe(fcppt::array::get<2>(axis_mappings[_orientation])));
}
}

sge::scenic::grid::object::object(
    sge::renderer::device::ffp_ref const _renderer,
    sge::camera::const_base_ref const _camera,
    sge::scenic::grid::orientation const _orientation,
    sge::scenic::grid::rect const &_rect,
    sge::scenic::grid::spacing const &_spacing,
    sge::scenic::grid::distance_to_origin const &_distance_to_origin,
    sge::image::color::any::object const &_color)
    : renderer_(_renderer),
      camera_(_camera),
      line_drawer_(fcppt::reference_to_base<sge::renderer::device::core>(_renderer))
{
  sge::line_drawer::scoped_lock llock(fcppt::make_ref(line_drawer_));

  for (sge::renderer::scalar y = _rect.pos().y(); y <= _rect.pos().y() + _rect.size().h();
       y += _spacing.get().h())
  {
    llock.value().push_back(sge::line_drawer::line(
        permute_vector_according_to_orientation(
            _orientation, sge::renderer::vector3(_rect.pos().x(), y, _distance_to_origin.get())),
        permute_vector_according_to_orientation(
            _orientation,
            sge::renderer::vector3(
                _rect.pos().x() + _rect.size().w(), y, _distance_to_origin.get())),
        _color,
        _color));
  }

  for (sge::renderer::scalar x = _rect.pos().x(); x <= _rect.pos().x() + _rect.size().w();
       x += _spacing.get().w())
  {
    llock.value().push_back(sge::line_drawer::line(
        permute_vector_according_to_orientation(
            _orientation, sge::renderer::vector3(x, _rect.pos().y(), _distance_to_origin.get())),
        permute_vector_according_to_orientation(
            _orientation,
            sge::renderer::vector3(
                x, _rect.pos().y() + _rect.size().h(), _distance_to_origin.get())),
        _color,
        _color));
  }
}

void sge::scenic::grid::object::render(
    sge::renderer::context::ffp &_context, sge::scenic::grid::depth_test const &_depth_test)
{
  if (fcppt::math::dim::contents(sge::renderer::target::viewport_size(_context.target())) == 0U)
  {
    return;
  }

  fcppt::optional::maybe_void(
      camera_.get().projection_matrix(),
      [&_context, &_depth_test, this](sge::camera::projection_matrix const &_projection)
      {
        sge::renderer::state::core::depth_stencil::object_unique_ptr const depth_state(
            renderer_.get().create_depth_stencil_state(
                sge::renderer::state::core::depth_stencil::parameters(
                    _depth_test.get()
                        ? sge::renderer::state::core::depth_stencil::depth::variant(
                              sge::renderer::state::core::depth_stencil::depth::enabled(
                                  sge::renderer::state::core::depth_stencil::depth::func::less,
                                  sge::renderer::state::core::depth_stencil::depth::write_enable(
                                      true)))
                        : sge::renderer::state::core::depth_stencil::depth::variant(
                              sge::renderer::state::core::depth_stencil::depth::off()),
                    sge::renderer::state::core::depth_stencil::stencil::variant(
                        sge::renderer::state::core::depth_stencil::stencil::off()))));

        sge::renderer::state::core::depth_stencil::scoped const depth_transform(
            fcppt::reference_to_base<sge::renderer::context::core>(fcppt::make_ref(_context)),
            fcppt::make_cref(*depth_state));

        sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
            renderer_.get().create_transform_state(
                sge::renderer::state::ffp::transform::parameters(_projection.get())));

        sge::renderer::state::ffp::transform::object_unique_ptr const world_state(
            renderer_.get().create_transform_state(sge::renderer::state::ffp::transform::parameters(
                sge::camera::matrix_conversion::world(camera_.get().coordinate_system()))));

        sge::renderer::state::ffp::transform::scoped const projection_transform(
            fcppt::make_ref(_context),
            sge::renderer::state::ffp::transform::mode::projection,
            fcppt::make_cref(*projection_state));

        sge::renderer::state::ffp::transform::scoped const world_transform(
            fcppt::make_ref(_context),
            sge::renderer::state::ffp::transform::mode::world,
            fcppt::make_cref(*world_state));

        line_drawer_.render(_context);
      });
}

sge::scenic::grid::object::~object() = default;
