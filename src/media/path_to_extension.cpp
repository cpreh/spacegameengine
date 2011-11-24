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


#include <sge/media/extension.hpp>
#include <sge/media/path_to_extension.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/string.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/path.hpp>


sge::media::optional_extension const
sge::media::path_to_extension(
	fcppt::filesystem::path const &_path
)
{
	fcppt::string const ext(
		fcppt::filesystem::extension_without_dot(
			_path
		)
	);

	return
		ext.empty()
		?
			sge::media::optional_extension()
		:
			sge::media::optional_extension(
				sge::media::extension(
					ext
				)
			)
		;
}
