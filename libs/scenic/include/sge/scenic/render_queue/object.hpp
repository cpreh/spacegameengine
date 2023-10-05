//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_QUEUE_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_QUEUE_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/buffer_ref.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/buffer_ref.hpp>
#include <sge/scenic/texture_manager_ref.hpp>
#include <sge/scenic/render_context/base_fwd.hpp>
#include <sge/scenic/render_context/material/object.hpp>
#include <sge/scenic/render_queue/index_type.hpp>
#include <sge/scenic/render_queue/mesh.hpp>
#include <sge/scenic/render_queue/state_change_count.hpp>
#include <sge/scenic/scene/material/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::scenic::render_queue
{
class object
{
  FCPPT_NONMOVABLE(object);

public:
  explicit object(sge::scenic::texture_manager_ref);

  void current_material(sge::scenic::scene::material::object const &);

  void current_vertex_buffer(sge::renderer::vertex::buffer_ref);

  void add_mesh(
      sge::renderer::matrix4 const &,
      sge::renderer::index::buffer_ref,
      sge::scenic::index_buffer_range const &);

  [[nodiscard]] sge::scenic::render_queue::state_change_count
  render(sge::scenic::render_context::base &); // NOLINT(google-runtime-references)

  ~object();

private:
  using material_sequence = std::vector<sge::scenic::render_context::material::object>;

  using vertex_buffer_sequence = std::vector<sge::renderer::vertex::buffer *>;

  using mesh_sequence = std::vector<sge::scenic::render_queue::mesh>;

  sge::scenic::texture_manager_ref const texture_manager_;
  material_sequence materials_;
  vertex_buffer_sequence vertex_buffers_;
  mesh_sequence meshes_;
  index_type current_material_;
  index_type current_vertex_buffer_;
};

}

#endif
