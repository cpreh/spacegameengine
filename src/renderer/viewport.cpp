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


#include <sge/renderer/viewport.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/text.hpp>
#include <ostream>

sge::renderer::viewport::viewport(
	pixel_pos const &_pos,
	screen_size const &_size
)
:
	pos_(_pos),
	size_(_size)
{}

sge::renderer::pixel_pos const &
sge::renderer::viewport::pos() const
{
	return pos_;
}

sge::renderer::screen_size const &
sge::renderer::viewport::size() const
{
	return size_;
}

fcppt::io::ostream &
sge::renderer::operator<<(
	fcppt::io::ostream &_stream,
	viewport const &_v
)
{
	return _stream
		<< _v.pos()
		<< FCPPT_TEXT(' ')
		<< _v.size();
}
