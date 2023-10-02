//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/core/exception.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/impl/vf/format.hpp>
#include <sge/line_drawer/impl/vf/part.hpp>
#include <sge/line_drawer/impl/vf/vertex_view.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/texture/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vertex/buffer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vf/proxy.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/labels/color.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/to_exception.hpp>

sge::line_drawer::object::object(sge::renderer::device::core_ref const _renderer)
    : renderer_(_renderer),
      vertex_declaration_(
          renderer_.get().create_vertex_declaration(sge::renderer::vertex::declaration_parameters(
              sge::renderer::vf::dynamic::make_format<sge::line_drawer::impl::vf::format>()))),
      blend_state_(renderer_.get().create_blend_state(sge::renderer::state::core::blend::parameters(
          sge::renderer::state::core::blend::alpha_variant{
              sge::renderer::state::core::blend::alpha_enabled(
                  sge::renderer::state::core::blend::combined(
                      sge::renderer::state::core::blend::source::src_alpha,
                      sge::renderer::state::core::blend::dest::inv_src_alpha))},
          sge::renderer::state::core::blend::write_mask_all()))),
      vb_(),
      lines_()
{
}

void sge::line_drawer::object::render(sge::renderer::context::core &_render_context)
{
  fcppt::optional::maybe_void(
      vb_,
      [&_render_context, this](sge::renderer::vertex::buffer_unique_ptr const &_buffer)
      {
        if (lines_.empty())
        {
          return;
        }

        sge::renderer::state::core::blend::scoped const scoped_blend(
            fcppt::make_ref(_render_context), fcppt::make_cref(*blend_state_));

        sge::renderer::vertex::scoped_declaration const scoped_decl(
            fcppt::make_ref(_render_context), fcppt::make_cref(*vertex_declaration_));

        sge::renderer::vertex::scoped_buffer const scoped_vb(
            fcppt::make_ref(_render_context), fcppt::make_cref(*_buffer));

        _render_context.render_nonindexed(
            sge::renderer::vertex::first(0U),
            sge::renderer::vertex::count(_buffer->linear_size()),
            sge::renderer::primitive_type::line_list);
      });
}

sge::line_drawer::object::~object() = default;

void sge::line_drawer::object::lock() {}

void sge::line_drawer::object::unlock()
{
  if (lines_.empty())
  {
    return;
  }

  auto const needed_size(fcppt::cast::size<sge::renderer::size_type>(lines_.size() * 2U));

  if (fcppt::optional::maybe(
          vb_,
          fcppt::const_(true),
          [needed_size](sge::renderer::vertex::buffer_unique_ptr const &_buffer)
          { return _buffer->linear_size() < needed_size; }))
  {
    vb_ = optional_vertex_buffer_unique_ptr(
        renderer_.get().create_vertex_buffer(sge::renderer::vertex::buffer_parameters(
            fcppt::make_cref(*vertex_declaration_),
            sge::renderer::vf::dynamic::part_index(0U),
            sge::renderer::vertex::count(needed_size),
            sge::renderer::resource_flags_field::null())));
  }

  // TODO(philipp): Better optional support for this
  sge::renderer::vertex::scoped_lock const vblock{
      fcppt::make_ref(*fcppt::optional::to_exception(
          this->vb_, [] { return sge::core::exception{FCPPT_TEXT("Line drawer VB not set!")}; })),
      sge::renderer::lock_mode::writeonly};

  sge::line_drawer::impl::vf::vertex_view const vertices{vblock.value()};

  sge::line_drawer::impl::vf::vertex_view::iterator vb_it{vertices.begin()};

  using vertex = sge::renderer::vf::vertex<sge::line_drawer::impl::vf::part>;

  // TODO(philipp): Improve this
  for (sge::line_drawer::line const &line : lines_)
  {
    *vb_it = vertex{
        sge::renderer::vf::labels::pos{} = line.begin(),
        sge::renderer::vf::labels::color{} = line.begin_color()};

    ++vb_it;

    *vb_it = vertex{
        sge::renderer::vf::labels::pos{} = line.end(),
        sge::renderer::vf::labels::color{} = line.end_color()};

    ++vb_it;
  }
}
