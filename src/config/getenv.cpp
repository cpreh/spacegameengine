/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/getenv.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config.hpp>
#ifdef FCPPT_WINDOWS_PLATFORM
#include <sge/windows/windows.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/text.hpp>
#else
#include <fcppt/from_std_string.hpp>
#include <cstdlib>
#endif

sge::config::optional_string const
sge::config::getenv(
	fcppt::string const &_name
)
{
#ifdef FCPPT_WINDOWS_PLATFORM
	fcppt::container::raw_vector<
		fcppt::char_type
	> buffer(32767);

	return
		::GetEnvironmentVariable(
			_name.c_str(),
			buffer.data(),
			buffer.size()
		) == 0
		?
			optional_string()
		:
			optional_string(
				buffer.data()
			);
#else
	char const *const ret(
		::std::getenv(
			fcppt::from_std_string(
				_name
			).c_str()
		)
	);

	return 
		ret
		?
			optional_string(
				fcppt::from_std_string(
					ret
				)
			)
		:
			optional_string();
#endif
}
