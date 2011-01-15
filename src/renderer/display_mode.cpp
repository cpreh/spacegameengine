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


#include <sge/renderer/display_mode.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/text.hpp>
#include <ostream>

sge::renderer::display_mode::display_mode(
	screen_size const &_size,
	renderer::bit_depth::type const _bit_depth,
	renderer::refresh_rate const _refresh_rate
)
:
	size_(_size),
	bit_depth_(_bit_depth),
	refresh_rate_(_refresh_rate)
{}

sge::renderer::screen_size const &
sge::renderer::display_mode::size() const
{
	return size_;
}

sge::renderer::bit_depth::type
sge::renderer::display_mode::bit_depth() const
{
	return bit_depth_;
}

sge::renderer::refresh_rate
sge::renderer::display_mode::refresh_rate() const
{
	return refresh_rate_;
}

bool
sge::renderer::operator==(
	display_mode const &_l,
	display_mode const &_r
)
{
	return
		_l.bit_depth() == _r.bit_depth()
		&& _l.size() == _r.size()
		&& _l.refresh_rate() == _r.refresh_rate();
}

bool
sge::renderer::operator!=(
	display_mode const &_l,
	display_mode const &_r
)
{
	return !(_l == _r);
}

fcppt::io::ostream &
sge::renderer::operator<<(
	fcppt::io::ostream &_stream,
	display_mode const &_mode
)
{
	return _stream
		<< FCPPT_TEXT('(')
		<< _mode.size().w()
		<< FCPPT_TEXT('x')
		<< _mode.size().h()
		<< FCPPT_TEXT('x')
		<< static_cast<unsigned>(
			_mode.bit_depth()
		)
		<< FCPPT_TEXT('@')
		<< _mode.refresh_rate()
		<< FCPPT_TEXT(')');
}
