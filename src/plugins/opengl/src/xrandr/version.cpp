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


#include <sge/opengl/xrandr/version.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <utility>
#include <fcppt/config/external_end.hpp>

#undef major
#undef minor


sge::opengl::xrandr::version::version(
	int const _major,
	int const _minor
)
:
	major_(
		_major
	),
	minor_(
		_minor
	)
{
}

int
sge::opengl::xrandr::version::major() const
{
	return
		major_;
}

int
sge::opengl::xrandr::version::minor() const
{
	return
		minor_;
}

bool
sge::opengl::xrandr::operator<(
	sge::opengl::xrandr::version const &_left,
	sge::opengl::xrandr::version const &_right
)
{
	auto const to_pair(
		[](
			sge::opengl::xrandr::version const &_version
		)
		{
			return
				std::make_pair(
					_version.major(),
					_version.minor()
				);
		}
	);

	return
		to_pair(
			_left
		)
		<
		to_pair(
			_right
		);
}

fcppt::io::ostream &
sge::opengl::xrandr::operator<<(
	fcppt::io::ostream &_stream,
	sge::opengl::xrandr::version const &_version
)
{
	return
		_stream
		<<
		_version.major()
		<<
		FCPPT_TEXT('.')
		<<
		_version.minor();
}
