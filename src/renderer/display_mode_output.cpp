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


#include <sge/renderer/bit_depth_bits.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/display_mode_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


fcppt::io::ostream &
sge::renderer::operator<<(
	fcppt::io::ostream &_stream,
	renderer::display_mode const &_mode
)
{
	return
		_stream
		<< FCPPT_TEXT('(')
		<< _mode.size().w()
		<< FCPPT_TEXT('x')
		<< _mode.size().h()
		<< FCPPT_TEXT('x')
		<< renderer::bit_depth_bits(
			_mode.bit_depth()
		)
		<< FCPPT_TEXT('@')
		<< _mode.refresh_rate()
		<< FCPPT_TEXT(')');
}
