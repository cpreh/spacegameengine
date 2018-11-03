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


#include <sge/opengl/pixel_store_context.hpp>
#include <sge/opengl/unpack_alignment.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::pixel_store_context::pixel_store_context()
:
	sge::opengl::context::base(),
	unpack_alignment_(
		4
	)
{
}

sge::opengl::pixel_store_context::~pixel_store_context()
{
}

void
sge::opengl::pixel_store_context::unpack_alignment(
	sge::opengl::unpack_alignment const _unpack_alignment
)
{
	unpack_alignment_ =
		_unpack_alignment;
}

sge::opengl::unpack_alignment
sge::opengl::pixel_store_context::unpack_alignment() const
{
	return
		unpack_alignment_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::pixel_store_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
