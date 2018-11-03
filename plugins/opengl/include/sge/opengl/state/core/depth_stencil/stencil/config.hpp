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


#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

class config
{
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLSTENCILFUNCSEPARATEPROC
	>
	gl_stencil_func_separate;

	typedef
	sge::opengl::fun_ref<
		PFNGLSTENCILOPSEPARATEPROC
	>
	gl_stencil_op_separate;

	config(
		gl_stencil_func_separate,
		gl_stencil_op_separate
	);

	gl_stencil_func_separate
	stencil_func_separate() const;

	gl_stencil_op_separate
	stencil_op_separate() const;
private:
	gl_stencil_func_separate stencil_func_separate_;

	gl_stencil_op_separate stencil_op_separate_;
};

}
}
}
}
}
}

#endif
