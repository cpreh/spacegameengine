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


#include <sge/config/media_path.hpp>
#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/shader/context.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>


sge::scenic::render_context::cg::manager::manager(
	sge::shader::context &_shader_context,
	sge::renderer::vertex_declaration &_vertex_declaration)
:
	sge::scenic::render_context::manager_base(),
	vertex_declaration_(
		_vertex_declaration),
	shader_(
		_shader_context,
		_vertex_declaration,
		sge::shader::vertex_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg")),
		sge::shader::pixel_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg"))),
	world_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4()),
	world_projection_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_projection"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			true),
		sge::renderer::matrix4()),
	world_inverse_transpose_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_it"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4()),
	diffuse_texture_(
		shader_,
		shader_.context().renderer(),
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"diffuse_texture"),
		sge::shader::parameter::planar_texture::optional_value())
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::cg::manager::create_context(
	sge::renderer::context::object &_context)
{
	return
		sge::scenic::render_context::base_unique_ptr(
			fcppt::make_unique_ptr<sge::scenic::render_context::cg::object>(
				fcppt::ref(
					*this),
				fcppt::ref(
					_context)));
}

sge::scenic::render_context::cg::manager::~manager()
{
}
