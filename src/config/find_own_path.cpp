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


#include "find_own_path.hpp"
#include <sge/config/make_files.hpp>
#include <sge/config/find_path.hpp>
#include <sge/config/exception.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

fcppt::filesystem::path const
sge::config::find_own_path(
	fcppt::string const &_what,
	path_vector const &_hard_paths
)
{
	config::optional_path const ret(
		config::find_path(
			config::make_files(
				FCPPT_TEXT("spacegameengine")
			),
			_what,
			_hard_paths
		)
	);

	if(
		!ret
	)
		throw config::exception(
			FCPPT_TEXT("sge path ")
			+ _what
			+ FCPPT_TEXT(" not found!")
		);
	
	return *ret;
}
