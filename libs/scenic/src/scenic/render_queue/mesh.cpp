//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/scenic/impl/number_multiplexer/object_impl.hpp>
#include <sge/scenic/render_queue/mesh.hpp>

namespace
{
sge::scenic::render_queue::sort_index create_sort_index(
    sge::scenic::render_queue::index_type const _material,
    sge::scenic::render_queue::index_type const _vertex_buffer)
{
  using multiplexer =
      sge::scenic::impl::number_multiplexer::object<sge::scenic::render_queue::sort_index>;

  return multiplexer()
      .append(
          multiplexer::bit_count(
              40U), // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          static_cast<sge::scenic::render_queue::sort_index>(_material))
      .append(
          multiplexer::bit_count(
              20U), // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          static_cast<sge::scenic::render_queue::sort_index>(_vertex_buffer))
      .value();
}
}

sge::scenic::render_queue::mesh::mesh(
    sge::scenic::render_queue::index_type const _material,
    sge::scenic::render_queue::index_type const _vertex_buffer,
    sge::renderer::matrix4 const _modelview,
    sge::renderer::index::buffer_ref const _index_buffer,
    sge::scenic::index_buffer_range const &_index_buffer_range)
    : material_(_material),
      vertex_buffer_(_vertex_buffer),
      sort_index_(create_sort_index(_material, _vertex_buffer)),
      modelview_(_modelview),
      index_buffer_(_index_buffer),
      index_buffer_range_(_index_buffer_range)
{
}

sge::scenic::render_queue::index_type sge::scenic::render_queue::mesh::material() const
{
  return material_;
}

sge::scenic::render_queue::index_type sge::scenic::render_queue::mesh::vertex_buffer() const
{
  return vertex_buffer_;
}

sge::renderer::matrix4 const &sge::scenic::render_queue::mesh::modelview() const
{
  return modelview_;
}

sge::renderer::index::buffer &sge::scenic::render_queue::mesh::index_buffer() const
{
  return index_buffer_.get();
}

sge::scenic::index_buffer_range const &sge::scenic::render_queue::mesh::index_buffer_range() const
{
  return index_buffer_range_;
}
