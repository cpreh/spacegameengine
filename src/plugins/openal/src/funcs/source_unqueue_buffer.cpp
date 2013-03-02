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


#include <sge/openal/buffer_id.hpp>
#include <sge/openal/openal.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_unqueue_buffer.hpp>
#include <sge/openal/funcs/source_unqueue_buffers.hpp>


sge::openal::buffer_id const
sge::openal::funcs::source_unqueue_buffer(
	sge::openal::source_id const _source
)
{
	ALuint result;

	sge::openal::funcs::source_unqueue_buffers(
		_source,
		&result,
		static_cast<
			ALsizei
		>(
			1
		)
	);

	return
		sge::openal::buffer_id(
			result
		);
}
