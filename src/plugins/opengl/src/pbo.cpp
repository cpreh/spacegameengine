/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../basic_buffer_impl.hpp"
#include "../pbo.hpp"
#include "../software_vbo.hpp"
#include "../vbo_util.hpp"
#include <boost/scoped_ptr.hpp>

namespace
{

boost::scoped_ptr<sge::ogl::vbo_base> impl;

}

sge::ogl::pbo_base::size_type const
sge::ogl::pbo_base::npos;

sge::ogl::pbo_base::~pbo_base()
{}

void sge::ogl::initialize_pbo()
{
	impl.reset(create_vbo_impl(sge::ogl::pbo_in_hardware()));
}

/*sge::ogl::pbo_base::iterator sge::ogl::pbo_base::end()
{
	return begin() + size();
}

sge::ogl::pbo_base::const_iterator sge::ogl::pbo_base::end() const
{
	return begin() + size();
}*/

GLenum sge::ogl::pixel_pack_buffer_type()
{
	if(GLEW_VERSION_2_1)
		return GL_PIXEL_PACK_BUFFER;
	if(GLEW_ARB_pixel_buffer_object)
		return GL_PIXEL_PACK_BUFFER_ARB;
	static GLenum software_id = software_vbo::unique_id();
	return software_id;
}

GLenum sge::ogl::pixel_unpack_buffer_type()
{
	if(GLEW_VERSION_2_1)
		return GL_PIXEL_UNPACK_BUFFER;
	if(GLEW_ARB_pixel_buffer_object)
		return GL_PIXEL_UNPACK_BUFFER_ARB;
	static GLenum software_id = software_vbo::unique_id();
	return software_id;
}

sge::ogl::vbo_base& sge::ogl::pbo_impl()
{
	return *impl;
}

bool sge::ogl::pbo_in_hardware()
{
	//return GLEW_VERSION_2_1 || GLEW_ARB_pixel_buffer_object;
	return false; // FIXME
}
