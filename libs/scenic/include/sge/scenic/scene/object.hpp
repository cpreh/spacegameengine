//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_SCENE_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SCENE_OBJECT_HPP_INCLUDED

#include <sge/camera/base_ref.hpp>
#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base_fwd.hpp>
#include <sge/scenic/render_queue/object_fwd.hpp>
#include <sge/scenic/scene/entity_fwd.hpp>
#include <sge/scenic/scene/identifier.hpp>
#include <sge/scenic/scene/manager_ref.hpp>
#include <sge/scenic/scene/mesh_path.hpp>
#include <sge/scenic/scene/object_fwd.hpp>
#include <sge/scenic/scene/prototype_unique_ptr.hpp>
#include <sge/scenic/scene/material/object.hpp>
#include <sge/scenic/scene/mesh/object_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/log/context_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sge::scenic::scene
{

class object
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_SCENIC_DETAIL_SYMBOL
  object(
      fcppt::log::context_reference,
      sge::scenic::scene::manager_ref,
      sge::viewport::manager_ref,
      sge::camera::base_ref,
      sge::scenic::scene::prototype_unique_ptr);

  SGE_SCENIC_DETAIL_SYMBOL
  void render(sge::scenic::render_context::base &); // NOLINT(google-runtime-references)

  SGE_SCENIC_DETAIL_SYMBOL
  ~object();

private:
  using mesh_map = std::map<sge::scenic::scene::mesh_path, sge::scenic::scene::mesh::object>;

  using material_map =
      std::map<sge::scenic::scene::identifier, sge::scenic::scene::material::object>;

  fcppt::log::context_reference const log_context_;
  sge::scenic::scene::manager_ref const scene_manager_;
  sge::camera::base_ref const camera_;
  sge::scenic::scene::prototype_unique_ptr const prototype_;
  sge::camera::perspective_projection_from_viewport camera_viewport_connection_;
  mesh_map mesh_name_to_instance_;
  material_map materials_;
  unsigned state_changes_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  void load_entities();

  void activate_lights(sge::scenic::render_context::base &); // NOLINT(google-runtime-references)

  void render_entity(sge::scenic::scene::entity const &, sge::scenic::render_queue::object &); // NOLINT(google-runtime-references)
};

}

#endif
