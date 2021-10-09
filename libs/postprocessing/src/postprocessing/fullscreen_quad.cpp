//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/postprocessing/fullscreen_quad.hpp>
#include <sge/postprocessing/vf/format.hpp>
#include <sge/postprocessing/vf/format_part.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/create_buffer_from_vertices.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <sge/renderer/vf/labels/texpos.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/array/make.hpp>
#include <fcppt/math/vector/static.hpp>

namespace
{

using vertex = sge::renderer::vf::vertex<sge::postprocessing::vf::format_part>;

}

sge::postprocessing::fullscreen_quad::fullscreen_quad(
    sge::renderer::device::core_ref const _renderer,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration)
    : vertex_declaration_{_vertex_declaration},
      vertex_buffer_{
          sge::renderer::vertex::create_buffer_from_vertices<sge::postprocessing::vf::format>(
              _renderer,
              _vertex_declaration,
              sge::renderer::resource_flags_field::null(),
              fcppt::array::make(
                  // Left top
                  vertex{
                      sge::renderer::vf::labels::pos{} =
                          sge::postprocessing::vf::position::packed_type{-1.0F, 1.0F},
                      sge::renderer::vf::labels::texpos<0>{} =
                          sge::postprocessing::vf::texcoord::packed_type{0.0F, 0.0F}},
                  // Left bottom
                  vertex{
                      sge::renderer::vf::labels::pos{} =
                          sge::postprocessing::vf::position::packed_type{-1.0F, -1.0F},
                      sge::renderer::vf::labels::texpos<0>{} =
                          sge::postprocessing::vf::texcoord::packed_type{0.0F, 1.0F}},
                  // Right top
                  vertex{
                      sge::renderer::vf::labels::pos{} =
                          sge::postprocessing::vf::position::packed_type{1.0F, 1.0F},
                      sge::renderer::vf::labels::texpos<0>{} =
                          sge::postprocessing::vf::texcoord::packed_type{1.0F, 0.0F}},
                  // Right bottom
                  vertex{
                      sge::renderer::vf::labels::pos{} =
                          sge::postprocessing::vf::position::packed_type{1.0F, -1.0F},
                      sge::renderer::vf::labels::texpos<0>{} =
                          sge::postprocessing::vf::texcoord::packed_type{1.0F, 1.0F}}))}
{
}

void sge::postprocessing::fullscreen_quad::render(sge::renderer::context::core &_context)
{
  sge::renderer::vertex::scoped_declaration const scoped_vd(
      fcppt::make_ref(_context), this->vertex_declaration_);

  sge::renderer::vertex::scoped_buffer const scoped_vb(
      fcppt::make_ref(_context), fcppt::make_cref(*this->vertex_buffer_));

  _context.render_nonindexed(
      sge::renderer::vertex::first{0U},
      sge::renderer::vertex::count{vertex_buffer_->linear_size()},
      sge::renderer::primitive_type::triangle_strip);
}

sge::postprocessing::fullscreen_quad::~fullscreen_quad() = default;

sge::renderer::vertex::declaration_unique_ptr
sge::postprocessing::fullscreen_quad::create_vertex_declaration(
    sge::renderer::device::core_ref const _renderer)
{
  return _renderer.get().create_vertex_declaration(sge::renderer::vertex::declaration_parameters(
      sge::renderer::vf::dynamic::make_format<sge::postprocessing::vf::format>()));
}
