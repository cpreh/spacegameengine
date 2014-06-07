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


#include <sge/cg/program/compile_options.hpp>

sge::cg::program::compile_options::compile_options()
:
	value_()
{
}

sge::cg::program::compile_options::compile_options(
	sge::cg::char_type const **_pointers)
:
	value_()
{
	for(;*_pointers;++_pointers)
		value_.push_back(
			sge::cg::string(
				*_pointers));
}

sge::cg::program::compile_options::compile_options(
	string_sequence const &_value)
:
	value_(
		_value)
{
}

sge::cg::program::compile_options::compile_options(
	string_sequence const &_value1,
	string_sequence const &_value2)
:
	value_(
		_value1)
{
	value_.insert(
		value_.end(),
		_value2.begin(),
		_value2.end());
}

sge::cg::program::compile_options::pointer_sequence
sge::cg::program::compile_options::pointers() const
{
	sge::cg::program::compile_options::pointer_sequence result;

	for(
		string_sequence::const_iterator it =
			value_.begin();
		it != value_.end();
		++it)
		result.push_back(
			it->c_str());

	result.push_back(
		0);

	return
		result;
}

sge::cg::program::compile_options::string_sequence const &
sge::cg::program::compile_options::value() const
{
	return
		value_;
}
