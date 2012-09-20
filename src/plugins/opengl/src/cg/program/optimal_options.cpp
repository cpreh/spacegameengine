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


#include <sge/cg/check_state.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/opengl/cg/program/optimal_options.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


sge::cg::program::compile_options const
sge::opengl::cg::program::optimal_options(
	sge::cg::context::object const &_context,
	sge::cg::profile::object const &_profile
)
{
	sge::cg::char_type const ** const ret(
#if CG_VERSION_NUM < 3100
		::cgGLGetOptimalOptions(
			_profile.get()
#else
		::cgGLGetContextOptimalOptions(
			_context.get(),
			_profile.get()
#endif
		)
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGLGetContextOptimalOptions failed"),
		sge::renderer::exception
	)

	FCPPT_ASSERT_ERROR(
		ret
		!=
		fcppt::null_ptr()
	);

	return
		sge::cg::program::compile_options(
			ret
		);
}
