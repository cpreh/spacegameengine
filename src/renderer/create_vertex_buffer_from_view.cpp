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


#include <sge/renderer/create_vertex_buffer_from_view.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <cstring>

sge::renderer::vertex_buffer_ptr const
sge::renderer::create_vertex_buffer_from_view(
	renderer::device_ptr const _device,
	renderer::vertex_declaration_ptr const _vertex_declaration,
	renderer::vf::dynamic::const_view const &_view,
	renderer::resource_flags_field const &_resource_flags
)
{
	renderer::vertex_buffer_ptr const buffer(
		_device->create_vertex_buffer(
			_vertex_declaration,
			_view.part_index(),
			_view.size(),
			_resource_flags
		)
	);

	renderer::scoped_vertex_lock const lock(
		buffer,
		renderer::lock_mode::writeonly
	);

	std::memcpy(
		lock.value().data(),
		_view.data(),
		_view.part().stride()
		* _view.size()
	);

	return buffer;
}
