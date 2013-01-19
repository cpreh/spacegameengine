/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


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
	scoped_buffers_()
{
	for(
		auto const &buffer : _vertex_buffers
	)
		fcppt::container::ptr::push_back_unique_ptr(
			scoped_buffers_,
			fcppt::make_unique_ptr<
				sge::renderer::vertex::scoped_buffer
			>(
				_context,
				buffer.get()
			)
		);
}

sge::renderer::vertex::scoped_declaration_and_buffers::~scoped_declaration_and_buffers()
{
}
