/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


fcppt::io::ostream &
sge::renderer::display_mode::operator<<(
	fcppt::io::ostream &_stream,
	sge::renderer::display_mode::object const &_mode
)
{
	_stream
		<< FCPPT_TEXT('(')
		<< _mode.pixel_size().get()
		<< FCPPT_TEXT("),(");

	if(
		_mode.dimensions()
	)
		_stream
			<< *_mode.dimensions();

	_stream
		<< FCPPT_TEXT(")@");

	if(
		_mode.refresh_rate()
	)
		_stream
			<< *_mode.refresh_rate();

	_stream
		<< FCPPT_TEXT(')');

	return
		_stream;
}
