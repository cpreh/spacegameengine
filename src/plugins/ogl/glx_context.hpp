/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OGL_GLX_CONTEXT_HPP_INCLUDED
#define SGE_OGL_GLX_CONTEXT_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "../../shared_ptr.hpp"
#include "../../x_display.hpp"
#include <GL/glx.h>

namespace sge
{
namespace ogl
{

class glx_context : boost::noncopyable {
public:
	glx_context(x_display_ptr, const XVisualInfo& vi);
	~glx_context();
	GLXContext& context();
private:
	x_display_ptr dsp;
	GLXContext c;
};

typedef shared_ptr<glx_context> glx_context_ptr;

}
}

#endif
