#ifndef SGE_SCENIC_SCENE_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SCENE_OBJECT_HPP_INCLUDED

#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/model/obj/material_map.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_queue/object_fwd.hpp>
#include <sge/scenic/scene/entity_sequence.hpp>
#include <sge/scenic/scene/prototype_scoped_ptr.hpp>
#include <sge/scenic/scene/prototype_unique_ptr.hpp>
#include <sge/scenic/render_context/base_fwd.hpp>
#include <sge/scenic/scene/material.hpp>
#include <sge/scenic/scene/manager_fwd.hpp>
#include <sge/scenic/scene/mesh/object_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
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
	FCPPT_MAKE_STRONG_TYPEDEF(
		boost::filesystem::path,
		model_base_path);

	FCPPT_MAKE_STRONG_TYPEDEF(
		boost::filesystem::path,
		material_base_path);

	FCPPT_MAKE_STRONG_TYPEDEF(
		boost::filesystem::path,
		texture_base_path);

	SGE_SCENIC_SYMBOL
	object(
		sge::scenic::scene::manager &,
		sge::viewport::manager &,
		sge::charconv::system &,
		sge::camera::first_person::object &,
		sge::scenic::scene::prototype_unique_ptr,
		model_base_path const &,
		material_base_path const &,
		texture_base_path const &);

	SGE_SCENIC_SYMBOL
	void
	render(
		sge::scenic::render_context::base &);

	SGE_SCENIC_SYMBOL
	~object();
private:
	typedef
	boost::ptr_map
	<
		sge::scenic::scene::identifier,
		sge::scenic::scene::mesh::object
	>
	mesh_map;

	typedef
	std::map
	<
		sge::scenic::scene::identifier,
		sge::scenic::scene::material
	>
	material_map;

	sge::scenic::scene::manager &scene_manager_;
	sge::camera::first_person::object &camera_;
	sge::charconv::system &charconv_system_;
	model_base_path const model_base_path_;
	material_base_path const material_base_path_;
	texture_base_path const texture_base_path_;
	sge::scenic::scene::prototype_scoped_ptr const prototype_;
	sge::camera::perspective_projection_from_viewport camera_viewport_connection_;
	mesh_map mesh_name_to_instance_;
	material_map materials_;
	unsigned state_changes_;

	void
	load_entities();

		/*
	void
	activate_lights(
		sge::renderer::context::object &);
		*/

	void
	render_entity(
		sge::scenic::scene::entity const &,
		sge::scenic::render_queue::object &);
};
}
}
}

#endif
