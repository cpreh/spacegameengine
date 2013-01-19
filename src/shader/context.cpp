/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/shader/context.hpp>


sge::shader::context::context(
	sge::renderer::device::core &_renderer)
:
	renderer_(
		_renderer),
	cg_context_(),
	vertex_profile_(
		_renderer.create_cg_profile(
			sge::cg::profile::shader_type::vertex)),
	pixel_profile_(
		_renderer.create_cg_profile(
			sge::cg::profile::shader_type::pixel))
{
}

sge::renderer::device::core &
sge::shader::context::renderer() const
{
	return
		renderer_;
}

sge::cg::context::object &
sge::shader::context::cg_context()
{
	return
		cg_context_;
}

sge::cg::context::object const &
sge::shader::context::cg_context() const
{
	return
		cg_context_;
}

sge::cg::profile::object const &
sge::shader::context::vertex_profile() const
{
	return
		vertex_profile_;
}

sge::cg::profile::object const &
sge::shader::context::pixel_profile() const
{
	return
		pixel_profile_;
}

sge::cg::program::compile_options const
sge::shader::context::vertex_compile_options() const
{
	return
		renderer_.cg_compile_options(
			cg_context_,
			vertex_profile_);
}

sge::cg::program::compile_options const
sge::shader::context::pixel_compile_options() const
{
	return
		renderer_.cg_compile_options(
			cg_context_,
			pixel_profile_);
}

sge::shader::context::~context()
{
}
