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


#ifndef SGE_OPENGL_TEXTURE_FORMAT_RESULT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FORMAT_RESULT_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/format_result_decl.hpp>


template<
	typename SGEFormat,
	typename GLFormat
>
sge::opengl::texture::format_result<
	SGEFormat,
	GLFormat
>::format_result(
	SGEFormat const _sge_format,
	GLFormat const _gl_format
)
:
	sge_format_{
		_sge_format
	},
	gl_format_{
		_gl_format
	}
{
}

template<
	typename SGEFormat,
	typename GLFormat
>
SGEFormat
sge::opengl::texture::format_result<
	SGEFormat,
	GLFormat
>::sge_format() const
{
	return
		sge_format_;
}

template<
	typename SGEFormat,
	typename GLFormat
>
GLFormat
sge::opengl::texture::format_result<
	SGEFormat,
	GLFormat
>::gl_format() const
{
	return
		gl_format_;
}

#endif
