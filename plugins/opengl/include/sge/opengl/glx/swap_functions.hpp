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


#ifndef SGE_OPENGL_GLX_SWAP_FUNCTIONS_HPP_INCLUDED
#define SGE_OPENGL_GLX_SWAP_FUNCTIONS_HPP_INCLUDED

#include <sge/opengl/glx/proc_address_function.hpp>
#include <sge/opengl/glx/swap_functions_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{

class swap_functions
{
public:
	explicit
	swap_functions(
		sge::opengl::glx::proc_address_function
	);

	typedef
	int(
		glx_swap_interval_sgi
	)(
		int
	);

	typedef
	fcppt::optional::reference<
		glx_swap_interval_sgi
	>
	optional_glx_swap_interval_sgi;

	typedef
	optional_glx_swap_interval_sgi::value_type
	glx_swap_interval_sgi_ref;

	typedef
	void(
		glx_swap_interval_ext
	)(
		Display *,
		GLXDrawable,
		int
	);

	typedef
	fcppt::optional::reference<
		glx_swap_interval_ext
	>
	optional_glx_swap_interval_ext;

	typedef
	optional_glx_swap_interval_ext::value_type
	glx_swap_interval_ext_ref;

	optional_glx_swap_interval_sgi
	swap_interval_sgi() const;

	optional_glx_swap_interval_ext
	swap_interval_ext() const;
private:
	optional_glx_swap_interval_sgi swap_interval_sgi_;

	optional_glx_swap_interval_ext swap_interval_ext_;
};

}
}
}

#endif
