/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/font/text_size_t.hpp>

sge::font::text_size_t::text_size_t(
	const dim size_,
	const string::const_iterator end_,
	const string::const_iterator next_begin_)
 : size_(size_),
   end_(end_),
   next_begin_(next_begin_)
{}
	
const sge::font::dim sge::font::text_size_t::size() const
{
	return size_;
}

sge::font::text_size_t::const_iterator sge::font::text_size_t::end() const
{
	return end_;
}

sge::font::text_size_t::const_iterator sge::font::text_size_t::next_begin() const
{
	return next_begin_;
}
