/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/occlusion_query/begin.hpp>
#include <sge/opengl/occlusion_query/context.hpp>
#include <sge/opengl/occlusion_query/id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>


void
sge::opengl::occlusion_query::begin(
	sge::opengl::occlusion_query::context const &_context,
	sge::opengl::occlusion_query::id const _id
)
{
	_context.begin_query()(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			_context.samples_target()
		),
		_id.get()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Beginning an occlusion query failed"),
		sge::renderer::exception
	)
}
