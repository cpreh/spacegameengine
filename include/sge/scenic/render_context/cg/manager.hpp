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


#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_MANAGER_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/manager_base.hpp>
#include <sge/scenic/render_context/cg/object_fwd.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <sge/shader/parameter/scalar.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
class manager
:
	public sge::scenic::render_context::manager_base
{
FCPPT_NONCOPYABLE(
	manager);
public:
	SGE_SCENIC_SYMBOL
	manager(
		sge::shader::context &,
		sge::renderer::vertex_declaration &);

	/* override */
	sge::scenic::render_context::base_unique_ptr
	create_context(
		sge::renderer::context::object &);

	SGE_SCENIC_SYMBOL
	~manager();
private:
	friend class sge::scenic::render_context::cg::object;

	static const std::size_t max_point_lights = 8u;

	typedef
	sge::shader::parameter::vector<sge::renderer::scalar,4u>
	float4_parameter;

	typedef
	boost::ptr_array<max_point_lights,float4_parameter>
	diffuse_point_light_colors;

	sge::renderer::vertex_declaration &vertex_declaration_;
	sge::shader::pair shader_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_projection_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_inverse_transpose_matrix_;
	sge::shader::parameter::scalar<int> point_light_count_;
	sge::shader::parameter::planar_texture diffuse_texture_;
};
}
}
}
}

#endif
