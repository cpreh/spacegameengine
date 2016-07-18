/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
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
		fcppt::log::context &,
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

	fcppt::log::context &log_context_;
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
