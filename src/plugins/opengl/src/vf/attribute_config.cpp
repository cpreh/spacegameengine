/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/vf/attribute_config.hpp>


sge::opengl::vf::attribute_config::attribute_config(
	sge::opengl::vf::attribute_config::gl_vertex_attrib_pointer _vertex_attrib_pointer,
	sge::opengl::vf::attribute_config::gl_enable_vertex_attrib_array _enable_vertex_attrib_array,
	sge::opengl::vf::attribute_config::gl_disable_vertex_attrib_array _disable_vertex_attrib_array
)
:
	vertex_attrib_pointer_(
		_vertex_attrib_pointer
	),
	enable_vertex_attrib_array_(
		_enable_vertex_attrib_array
	),
	disable_vertex_attrib_array_(
		_disable_vertex_attrib_array
	)
{
}

sge::opengl::vf::attribute_config::gl_vertex_attrib_pointer
sge::opengl::vf::attribute_config::vertex_attrib_pointer() const
{
	return
		vertex_attrib_pointer_;
}

sge::opengl::vf::attribute_config::gl_enable_vertex_attrib_array
sge::opengl::vf::attribute_config::enable_vertex_attrib_array() const
{
	return
		enable_vertex_attrib_array_;
}

sge::opengl::vf::attribute_config::gl_disable_vertex_attrib_array
sge::opengl::vf::attribute_config::disable_vertex_attrib_array() const
{
	return
		disable_vertex_attrib_array_;
}
