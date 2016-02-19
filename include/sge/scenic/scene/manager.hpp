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


#ifndef SGE_SCENIC_SCENE_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MANAGER_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/scenic/render_context/manager_base_unique_ptr.hpp>
#include <sge/scenic/scene/prefer_cg_context.hpp>
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
	SGE_SCENIC_DETAIL_SYMBOL
	manager(
		sge::renderer::device::core &,
		sge::image2d::system &,
		sge::scenic::scene::prefer_cg_context const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::base_unique_ptr
	create_render_context(
		sge::renderer::context::core &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::device::core &
	renderer() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::vertex::declaration &
	vertex_declaration();

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::texture_manager &
	texture_manager();

	SGE_SCENIC_DETAIL_SYMBOL
	sge::shader::context &
	shader_context();

	SGE_SCENIC_DETAIL_SYMBOL
	~manager();
private:
	sge::renderer::device::core &renderer_;
	sge::renderer::vertex::declaration_unique_ptr const mesh_vertex_declaration_;
	sge::scenic::texture_manager texture_manager_;
	sge::shader::context shader_context_;
	sge::scenic::render_context::manager_base_unique_ptr render_context_manager_;
};
}
}
}

#endif
