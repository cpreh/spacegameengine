/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/resource_tree/path.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sge::resource_tree::path::path()
:
	elements_()
{
}

sge::resource_tree::path &
sge::resource_tree::path::operator/=(
	fcppt::string const &s)
{
	elements_.push_back(
		s);
	return *this;
}

sge::resource_tree::path
sge::resource_tree::path::operator/(
	fcppt::string const &s) const
{
	path result(
		*this);

	result /= s;

	return result;
}

sge::resource_tree::path::const_iterator const
sge::resource_tree::path::begin() const
{
	return elements_.begin();
}

sge::resource_tree::path::const_iterator const
sge::resource_tree::path::end() const
{
	return elements_.end();
}

bool
sge::resource_tree::path::operator==(
	sge::resource_tree::path const &_p) const
{
	return
		elements_.size() == _p.elements_.size() &&
		std::equal(
			elements_.begin(),
			elements_.end(),
			_p.elements_.begin());
}

fcppt::string
sge::resource_tree::path::back() const
{
	return elements_.back();
}

fcppt::string
sge::resource_tree::path::string() const
{
	fcppt::string result;

	for(
		element_sequence::const_iterator it =
			elements_.begin();
		it != elements_.end();
		++it)
	{
		if(it != std::prev(elements_.end()))
			result += (*it)+FCPPT_TEXT("/");
		else
			result += (*it);
	}

	return result;
}
