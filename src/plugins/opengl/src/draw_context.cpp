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


#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/draw_context.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::draw_context::draw_context()
:
	sge::opengl::context::system::base(),
	draw_range_elements_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_1_2
		)
		?
			optional_draw_range_elements(
				sge::opengl::deref_fun_ptr(
					glDrawRangeElements
				)
			)
		:
			glDrawRangeElementsEXT
			!=
			nullptr
			?
				optional_draw_range_elements(
					sge::opengl::deref_fun_ptr(
						glDrawRangeElementsEXT
					)
				)
			:
				optional_draw_range_elements()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::draw_context::~draw_context()
{
}

sge::opengl::draw_context::optional_draw_range_elements const
sge::opengl::draw_context::draw_range_elements() const
{
	return
		draw_range_elements_;
}

sge::opengl::context::system::id const
sge::opengl::draw_context::static_id(
	sge::opengl::context::system::make_id()
);
