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


#include <sge/config/getenv.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/optional_impl.hpp>
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/windows.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/text.hpp>
#else
#include <fcppt/from_std_string.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>
#endif

sge::config::optional_string const
sge::config::getenv(
	fcppt::string const &_name
)
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	// an environment variable cannot be longer than 32767 characters
	fcppt::container::raw_vector<
		fcppt::char_type
	> buffer(
		32767
	);

	DWORD const ret(
		::GetEnvironmentVariable(
			_name.c_str(),
			buffer.data(),
			static_cast<
				DWORD
			>(
				buffer.size()
			)
		)
	);

	if(
		ret == 0
	)
		return config::optional_string();

	FCPPT_ASSERT_ERROR(
		ret <=
		static_cast<
			DWORD
		>(
			buffer.size()
		)
	);

	return
			config::optional_string(
				fcppt::string(
					buffer.data()
				)
			);
#else
	char const *const ret(
		::std::getenv(
			fcppt::to_std_string(
				_name
			).c_str()
		)
	);

	return
		ret
		?
			config::optional_string(
				fcppt::from_std_string(
					ret
				)
			)
		:
			config::optional_string();
#endif
}
