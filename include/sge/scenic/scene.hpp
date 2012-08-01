/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SCENIC_SCENE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/model/obj/material_map.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/renderer/light/object.hpp>
#include <sge/scenic/material_base_path.hpp>
#include <sge/scenic/mesh.hpp>
#include <sge/parse/json/array_fwd.hpp>
#include <sge/scenic/model_base_path.hpp>
#include <sge/scenic/scene_description_file.hpp>
#include <sge/scenic/texture_base_path.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
class scene
{
FCPPT_NONCOPYABLE(
	scene);
public:
	SGE_SCENIC_SYMBOL
	scene(
		sge::renderer::device &,
		sge::image2d::system &,
	    sge::viewport::manager &,
		sge::input::keyboard::device &,
		sge::input::mouse::device &,
		sge::scenic::scene_description_file const &,
		sge::scenic::model_base_path const &,
		sge::scenic::material_base_path const &,
		sge::scenic::texture_base_path const &);

	void
	render(
		sge::renderer::context::object &);

	SGE_SCENIC_SYMBOL
	~scene();
private:
	typedef
	boost::ptr_map
	<
		fcppt::string,
		sge::model::obj::instance
	>
	model_name_to_instance_map;

	typedef
	boost::ptr_vector<sge::scenic::mesh>
	mesh_sequence;

	typedef
	std::vector<sge::renderer::light::object>
	light_sequence;

	sge::scenic::texture_base_path const texture_base_path_;
	sge::scenic::model_base_path const model_base_path_;
	sge::scenic::material_base_path const material_base_path_;
	sge::renderer::vertex_declaration_scoped_ptr const model_vertex_declaration_;
	sge::scenic::texture_manager texture_manager_;
	sge::model::obj::material_map materials_;
	sge::camera::first_person::object camera_;
	fcppt::scoped_ptr<sge::camera::perspective_projection_from_viewport> camera_viewport_connection_;
	model_name_to_instance_map model_name_to_instance_;
	mesh_sequence meshes_;
	light_sequence lights_;
	sge::timer::basic<sge::timer::clocks::standard> camera_timer_;

	void
	enable_lights(
		sge::renderer::context::object &);

	void
	render_mesh(
		sge::scenic::mesh const &,
		sge::renderer::context::object &);

	void
	load_camera(
		sge::parse::json::object const &,
		sge::renderer::device &,
		sge::viewport::manager &);

	void
	load_meshes(
		sge::renderer::device &,
		sge::parse::json::array const &);

	void
	load_mesh(
		sge::renderer::device &,
		sge::parse::json::object const &);

	sge::model::obj::instance &
	insert_model_if_necessary(
		sge::renderer::device &,
		fcppt::string const &);
};
}
}

#endif
