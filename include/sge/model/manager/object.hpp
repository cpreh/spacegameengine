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


#ifndef SGE_MODEL_MANAGER_OBJECT_HPP_INCLUDED
#define SGE_MODEL_MANAGER_OBJECT_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/model/manager/model_directory.hpp>
#include <sge/model/manager/symbol.hpp>
#include <sge/model/manager/texture_directory.hpp>
#include <sge/model/manager/instance/identifier.hpp>
#include <sge/model/manager/instance/sequence.hpp>
#include <sge/model/obj/loader_scoped_ptr.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace manager
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_MODEL_MANAGER_SYMBOL
	object(
		sge::renderer::device &,
		sge::image2d::system &,
		sge::camera::base &,
		sge::model::manager::model_directory const &,
		sge::model::manager::texture_directory const &);

	SGE_MODEL_MANAGER_SYMBOL
	void
	render(
		sge::renderer::context::object &,
		sge::model::manager::instance::sequence const &);

	SGE_MODEL_MANAGER_SYMBOL
	~object();
private:
	friend class sge::model::manager::instance::object;

	typedef
	boost::ptr_map
	<
		sge::model::manager::instance::identifier,
		sge::renderer::vertex_buffer
	>
	vertex_buffer_map;

	typedef
	boost::ptr_map
	<
		sge::model::manager::instance::identifier,
		sge::renderer::texture::planar
	>
	texture_map;

	sge::renderer::device &renderer_;
	sge::camera::base &camera_;
	sge::renderer::vertex_declaration_scoped_ptr vertex_declaration_;
	vertex_buffer_map identifier_to_vertex_buffer_;
	texture_map identifier_to_texture_;
	sge::model::obj::loader_scoped_ptr model_loader_;
};
}
}
}

#endif
