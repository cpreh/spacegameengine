/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/filesystem/readlink.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/config.h>
#ifdef SGE_POSIX_PLATFORM
#include <sge/container/raw_vector_impl.hpp>
#include <sge/error/strerrno.hpp>
#include <sge/iconv.hpp>
#include <unistd.h>
#include <cerrno>
#endif

sge::filesystem::path const
sge::filesystem::readlink(
	sge::filesystem::path const &link
)
{
#ifdef SGE_POSIX_PLATFORM
	container::raw_vector<
		char
	> buf;

	buf.reserve(
		512
	);

	for (;;)
	{
		ssize_t const ret(
			::readlink(
				link.string().c_str(),
				buf.data(),
				buf.capacity()
			)
		);

		if(ret == -1)
		{
			if(errno == ENAMETOOLONG)
			{
				buf.reserve(
					buf.capacity() * 2
				);
				continue;
			}

			throw exception(
				SGE_TEXT("readlink failed: ")
				+ error::strerrno()
			);
		}

		buf.resize_uninitialized(
			ret
		);

		buf.push_back(0);

		return path(
			iconv(
				buf.data()
			)
		);
	}
#else
	throw exception(
		SGE_TEXT("readlink not supported!")
	);
#endif
}
