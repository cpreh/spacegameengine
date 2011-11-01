/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_TEXTURE_MULTI_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MULTI_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/texture/multi_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class multi_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(
		multi_context
	);
public:
	multi_context();

	~multi_context();

	bool
	is_supported() const;

	PFNGLACTIVETEXTUREPROC
	active_texture() const;

	PFNGLCLIENTACTIVETEXTUREPROC
	client_active_texture() const;

	GLint
	max_level() const;

	typedef void needs_before;

	static context::id const static_id;
private:
	bool const
		is_native_,
		is_arb_;

	PFNGLACTIVETEXTUREPROC const active_texture_;

	PFNGLCLIENTACTIVETEXTUREPROC const client_active_texture_;

	GLint const max_level_;
};

}
}
}

#endif
