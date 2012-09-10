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


#ifndef SGE_SCENIC_SCENE_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MANAGER_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/scenic/render_context/manager_base_scoped_ptr.hpp>
#include <sge/shader/context.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
class manager
{
FCPPT_NONCOPYABLE(
	manager);
public:
	SGE_SCENIC_SYMBOL
	manager(
		sge::renderer::device &,
		sge::image2d::system &);

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::base_unique_ptr
	create_render_context(
		sge::renderer::context::object &);

	SGE_SCENIC_SYMBOL
	sge::renderer::device &
	renderer() const;

	SGE_SCENIC_SYMBOL
	sge::renderer::vertex_declaration &
	vertex_declaration();

	SGE_SCENIC_SYMBOL
	sge::scenic::texture_manager &
	texture_manager();

	SGE_SCENIC_SYMBOL
	~manager();
private:
	sge::renderer::device &renderer_;
	sge::renderer::vertex_declaration_scoped_ptr const mesh_vertex_declaration_;
	sge::scenic::texture_manager texture_manager_;
	sge::shader::context shader_context_;
	sge::scenic::render_context::manager_base_scoped_ptr render_context_manager_;
};
}
}
}

#endif
