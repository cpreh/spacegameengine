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


#include <sge/input/exception.hpp>
#include <sge/wlinput/focus/mmap.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/mman.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


sge::wlinput::focus::mmap::mmap(
	awl::backends::posix::fd const _fd,
	std::uint32_t const _size
)
:
	size_{
		_size
	},
	string_{
		fcppt::cast::from_void_ptr<
			char *
		>(
			::mmap(
				nullptr,
				size_,
				PROT_READ,
				MAP_SHARED,
				_fd.get(),
				0
			)
		)
	}
{
	if(
		string_
		==
		MAP_FAILED
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Cannot map keymap")
			};
}

sge::wlinput::focus::mmap::~mmap()
{
	FCPPT_ASSERT_ERROR(
		::munmap(
			string_,
			size_
		)
		==
		0
	);

}

char const *
sge::wlinput::focus::mmap::string() const
{
	return
		string_;
}
