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


#include <sge/openal/buffer_holder.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/logger.hpp>
#include <sge/openal/funcs/delete_buffer.hpp>
#include <sge/openal/funcs/gen_buffer.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>


sge::openal::buffer_holder::buffer_holder()
:
	buffer_(
		sge::openal::funcs::gen_buffer()
	)
{
}

sge::openal::buffer_holder::~buffer_holder()
{
	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("Deleting a buffer")
	);

	sge::openal::funcs::delete_buffer(
		buffer_
	);
}

sge::openal::buffer_id const
sge::openal::buffer_holder::get() const
{
	return buffer_;
}
