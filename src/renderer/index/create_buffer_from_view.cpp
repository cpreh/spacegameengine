/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/create_buffer_from_view.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::index::buffer_unique_ptr
sge::renderer::index::create_buffer_from_view(
	sge::renderer::device::core &_device,
	sge::renderer::index::dynamic::const_view const &_view,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	sge::renderer::index::buffer_unique_ptr buffer(
		_device.create_index_buffer(
			sge::renderer::index::buffer_parameters(
				_view.format(),
				sge::renderer::index::count(
					_view.size()
				),
				_resource_flags
			)
		)
	);

	sge::renderer::index::scoped_lock const lock(
		*buffer,
		sge::renderer::lock_mode::writeonly
	);

	std::memcpy(
		lock.value().data(),
		_view.data(),
		sge::renderer::index::dynamic::format_stride(
			_view.format()
		)
		*
		_view.size()
	);

	return
		std::move(
			buffer
		);
}
