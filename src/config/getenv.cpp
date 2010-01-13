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


#include <sge/config/getenv.hpp>
#include <sge/config/no_such_env_var.hpp>
#include <fcppt/config.h>
#ifdef FCPPT_WINDOWS_PLATFORM
#include <sge/windows/windows.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/text.hpp>
#else
#include <fcppt/iconv.hpp>
#include <cstdlib>
#endif

fcppt::string const
sge::config::getenv(
	fcppt::string const &s
)
{
#ifdef FCPPT_WINDOWS_PLATFORM
	fcppt::container::raw_vector<
		fcppt::char_type
	> home_dir(32767);

	if(
		GetEnvironmentVariable(
			FCPPT_TEXT("USERPROFILE"),
			home_dir.data(),
			home_dir.size()
		) == 0
	)
		throw no_such_env_var(
			s
		);

	return home_dir.data();
#else
	char const *const ret(
		::std::getenv(
			fcppt::iconv(
				s
			).c_str()
		)
	);

	if(!ret)
		throw no_such_env_var(
			s
		);

	return fcppt::iconv(
		ret
	);
#endif
}
