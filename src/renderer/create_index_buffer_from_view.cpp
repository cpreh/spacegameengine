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


#include <sge/renderer/create_index_buffer_from_view.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>


sge::renderer::index_buffer_ptr const
sge::renderer::create_index_buffer_from_view(
	renderer::device &_device,
	index::dynamic::const_view const &_view,
	renderer::resource_flags_field const &_resource_flags
)
{
	renderer::index_buffer_ptr const buffer(
		_device.create_index_buffer(
			_view.format(),
			sge::renderer::index_count(
				_view.size()
			),
			_resource_flags
		)
	);

	renderer::scoped_index_lock const lock(
		*buffer,
		renderer::lock_mode::writeonly
	);

	std::memcpy(
		lock.value().data(),
		_view.data(),
		renderer::index::dynamic::format_stride(
			_view.format()
		)
		*
		_view.size()
	);

	return buffer;
}
