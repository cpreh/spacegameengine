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
#include <fcppt/algorithm/join_strings.hpp>


sge::resource_tree::path::path()
:
	elements_()
{
}

sge::resource_tree::path &
sge::resource_tree::path::operator/=(
	fcppt::string const &_path
)
{
	elements_.push_back(
		_path
	);

	return
		*this;
}

sge::resource_tree::path
sge::resource_tree::path::operator/(
	fcppt::string const &_path
) const
{
	path result(
		*this
	);

	result /= _path;

	return
		result;
}

sge::resource_tree::path::const_iterator
sge::resource_tree::path::begin() const
{
	return
		elements_.begin();
}

sge::resource_tree::path::const_iterator
sge::resource_tree::path::end() const
{
	return
		elements_.end();
}

bool
sge::resource_tree::path::operator==(
	sge::resource_tree::path const &_other
) const
{
	return
		_other.elements_
		==
		elements_;
}

fcppt::string const &
sge::resource_tree::path::back() const
{
	return
		elements_.back();
}

fcppt::string
sge::resource_tree::path::string() const
{
	return
		fcppt::algorithm::join_strings(
			elements_,
			FCPPT_TEXT("/")
		);
}
