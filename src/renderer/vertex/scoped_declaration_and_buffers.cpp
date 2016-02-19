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


#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>


sge::renderer::vertex::scoped_declaration_and_buffers::scoped_declaration_and_buffers(
	sge::renderer::context::core &_context,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::renderer::vertex::const_buffer_ref_container const &_vertex_buffers
)
:
	scoped_declaration_(
		_context,
		_vertex_declaration
	),
	scoped_buffers_(
		fcppt::algorithm::map<
			scoped_buffer_vector
		>(
			_vertex_buffers,
			[
				&_context
			](
				sge::renderer::vertex::const_buffer_ref const _ref
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::renderer::vertex::scoped_buffer
					>(
						_context,
						_ref.get()
					);
			}
		)
	)
{
}

sge::renderer::vertex::scoped_declaration_and_buffers::~scoped_declaration_and_buffers()
{
}
