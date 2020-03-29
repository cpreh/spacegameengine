//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_SCENE_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SCENE_OBJECT_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base_fwd.hpp>
#include <sge/scenic/render_queue/object_fwd.hpp>
#include <sge/scenic/scene/entity_sequence.hpp>
#include <sge/scenic/scene/manager_fwd.hpp>
#include <sge/scenic/scene/mesh_path.hpp>
#include <sge/scenic/scene/prototype_unique_ptr.hpp>
#include <sge/scenic/scene/material/object.hpp>
#include <sge/scenic/scene/mesh/object_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		fcppt::log::context_reference,
		sge::scenic::scene::manager &,
		sge::viewport::manager &,
		sge::camera::base &,
		sge::scenic::scene::prototype_unique_ptr);

	SGE_SCENIC_DETAIL_SYMBOL
	void
	render(
		sge::scenic::render_context::base &);

	SGE_SCENIC_DETAIL_SYMBOL
	~object();
private:
	typedef
	std::map
	<
		sge::scenic::scene::mesh_path,
		sge::scenic::scene::mesh::object
	>
	mesh_map;

	typedef
	std::map
	<
		sge::scenic::scene::identifier,
		sge::scenic::scene::material::object
	>
	material_map;

	fcppt::log::context_reference const log_context_;
	sge::scenic::scene::manager &scene_manager_;
	sge::camera::base &camera_;
	sge::scenic::scene::prototype_unique_ptr const prototype_;
	sge::camera::perspective_projection_from_viewport camera_viewport_connection_;
	mesh_map mesh_name_to_instance_;
	material_map materials_;
	unsigned state_changes_;

	void
	load_entities();

	void
	activate_lights(
		sge::scenic::render_context::base &);

	void
	render_entity(
		sge::scenic::scene::entity const &,
		sge::scenic::render_queue::object &);
};
}
}
}

#endif
