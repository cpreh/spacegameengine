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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vertex/context.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/opengl/vertex/set_declaration.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/map.hpp>


void
sge::opengl::vertex::set_declaration(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::const_optional_declaration_ref const &_opt_declaration
)
{
	sge::opengl::context::use<
		sge::opengl::vertex::context
	>(
		_context
	).vertex_declaration(
		fcppt::optional::map(
			_opt_declaration,
			[](
				fcppt::reference_wrapper<
					sge::renderer::vertex::declaration const
				> const _declaration
			)
			{
				return
					fcppt::make_cref(
						fcppt::cast::static_downcast<
							sge::opengl::vertex::declaration const &
						>(
							_declaration.get()
						)
					);
			}
		)
	);
}
