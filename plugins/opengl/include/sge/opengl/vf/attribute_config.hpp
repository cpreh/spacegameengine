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


#ifndef SGE_OPENGL_VF_ATTRIBUTE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/vf/attribute_config_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class attribute_config
{
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLVERTEXATTRIBPOINTERPROC
	>
	gl_vertex_attrib_pointer;

	typedef
	sge::opengl::fun_ref<
		PFNGLENABLEVERTEXATTRIBARRAYPROC
	>
	gl_enable_vertex_attrib_array;

	typedef
	sge::opengl::fun_ref<
		PFNGLDISABLEVERTEXATTRIBARRAYPROC
	>
	gl_disable_vertex_attrib_array;

	attribute_config(
		gl_vertex_attrib_pointer,
		gl_enable_vertex_attrib_array,
		gl_disable_vertex_attrib_array
	);

	gl_vertex_attrib_pointer
	vertex_attrib_pointer() const;

	gl_enable_vertex_attrib_array
	enable_vertex_attrib_array() const;

	gl_disable_vertex_attrib_array
	disable_vertex_attrib_array() const;
private:
	gl_vertex_attrib_pointer vertex_attrib_pointer_;

	gl_enable_vertex_attrib_array enable_vertex_attrib_array_;

	gl_disable_vertex_attrib_array disable_vertex_attrib_array_;
};

}
}
}

#endif
