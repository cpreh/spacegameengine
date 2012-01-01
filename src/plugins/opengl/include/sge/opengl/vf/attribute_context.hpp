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


#ifndef SGE_OPENGL_VF_ATTRIBUTE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/vf/attribute_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class attribute_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(
		attribute_context
	);
public:
	attribute_context();

	~attribute_context();

	bool
	is_supported() const;

	PFNGLVERTEXATTRIBPOINTERPROC
	vertex_attrib_pointer() const;

	PFNGLENABLEVERTEXATTRIBARRAYPROC
	enable_vertex_attrib_array() const;

	PFNGLDISABLEVERTEXATTRIBARRAYPROC
	disable_vertex_attrib_array() const;

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	bool const
		is_native_,
		is_arb_;

	PFNGLVERTEXATTRIBPOINTERPROC const vertex_attrib_pointer_;

	PFNGLENABLEVERTEXATTRIBARRAYPROC const enable_vertex_attrib_array_;

	PFNGLDISABLEVERTEXATTRIBARRAYPROC const disable_vertex_attrib_array_;
};

}
}
}

#endif
