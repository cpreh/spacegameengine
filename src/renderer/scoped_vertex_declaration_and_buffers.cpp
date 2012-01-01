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


#include <sge/renderer/const_vertex_buffer_ref_container.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration_and_buffers.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


sge::renderer::scoped_vertex_declaration_and_buffers::scoped_vertex_declaration_and_buffers(
	renderer::device &_device,
	renderer::vertex_declaration const &_vertex_declaration,
	renderer::const_vertex_buffer_ref_container const &_vertex_buffers
)
:
	scoped_declaration_(
		_device,
		_vertex_declaration
	)
{
	for(
		renderer::const_vertex_buffer_ref_container::const_iterator it(
			_vertex_buffers.begin()
		);
		it != _vertex_buffers.end();
		++it
	)
		fcppt::container::ptr::push_back_unique_ptr(
			scoped_buffers_,
			fcppt::make_unique_ptr<
				sge::renderer::scoped_vertex_buffer
			>(
				fcppt::ref(
					_device
				),
				*it
			)
		);
}

sge::renderer::scoped_vertex_declaration_and_buffers::~scoped_vertex_declaration_and_buffers()
{
}
