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


#include <sge/opengl/state/deferred/blend_func.hpp>
#include <sge/opengl/state/convert/dest_blend_func.hpp>
#include <sge/opengl/state/convert/source_blend_func.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::state::deferred::blend_func(
	deferred::parameters const &,
	sge::renderer::state::list const &_list
)
{
	::glBlendFunc(
		state::convert::source_blend_func(
			_list.get<
				renderer::state::source_blend_func::type
			>()
		),
		state::convert::dest_blend_func(
			_list.get<
				renderer::state::dest_blend_func::type
			>()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBlendFunc failed"),
		sge::renderer::exception
	)
}
