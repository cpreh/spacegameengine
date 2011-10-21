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


#include <sge/parse/json/path.hpp>
#include <fcppt/string.hpp>


sge::parse::json::path::path(
	const_iterator const _begin,
	const_iterator const _end)
:
	sequence_(
		_begin,
		_end)
{
}

sge::parse::json::path::path(
	fcppt::string const &s)
:
	sequence_()
{
	sequence_.push_back(
		s);
}

sge::parse::json::path::const_iterator
sge::parse::json::path::begin() const
{
	return sequence_.begin();
}

sge::parse::json::path::const_iterator
sge::parse::json::path::end() const
{
	return sequence_.end();
}

sge::parse::json::path::size_type
sge::parse::json::path::size() const
{
	return sequence_.size();
}

sge::parse::json::path::const_reference
sge::parse::json::path::back() const
{
	return sequence_.back();
}

bool
sge::parse::json::path::empty() const
{
	return sequence_.empty();
}

sge::parse::json::path &
sge::parse::json::path::operator/(
	fcppt::string const &s)
{
	sequence_.push_back(
		s);
	return *this;
}
