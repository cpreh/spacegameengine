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



#include <sge/renderer/display_mode.hpp>
#include <sge/text.hpp>
#include <ostream>
	
sge::renderer::display_mode::display_mode(
	screen_size const &size_,
	renderer::bit_depth::type const bit_depth_,
	refresh_rate_type const refresh_rate_)
 :
	size_(size_),
	bit_depth_(bit_depth_),
	refresh_rate_(refresh_rate_)
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

sge::renderer::refresh_rate_type
sge::renderer::display_mode::refresh_rate() const
{
	return refresh_rate_;
}

bool sge::renderer::operator== (
	display_mode const &l,
	display_mode const &r)
{
	return l.bit_depth() == r.bit_depth()
		&& l.size() == r.size()
		&& l.refresh_rate() == r.refresh_rate();
}

bool sge::renderer::operator!= (
	display_mode const &l,
	display_mode const &r)
{
	return !(l==r);
}

sge::ostream &
sge::renderer::operator<<(
	ostream &s,
	display_mode const &mode)
{
	return s
		<< SGE_TEXT('(')
		<< mode.size().w()
		<< SGE_TEXT('x')
		<< mode.size().h()
		<< SGE_TEXT('x')
		<< static_cast<unsigned>(
			mode.bit_depth())
		<< SGE_TEXT('@')
		<< mode.refresh_rate()
		<< SGE_TEXT(')');
}
