/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/cg/char_type.hpp>
#include <sge/cg/string.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::cg::program::compile_options::compile_options()
:
	value_()
{
}

sge::cg::program::compile_options::compile_options(
	sge::cg::char_type const **_pointers
)
:
	value_()
{
	// TODO: Refactor this
	for(;*_pointers;++_pointers)
		value_.push_back(
			sge::cg::string(
				*_pointers));
}

sge::cg::program::compile_options::compile_options(
	string_sequence _value
)
:
	value_(
		std::move(
			_value
		)
	)
{
}

sge::cg::program::compile_options::pointer_sequence
sge::cg::program::compile_options::pointers() const
{
	sge::cg::program::compile_options::pointer_sequence result{
		fcppt::algorithm::map<
			sge::cg::program::compile_options::pointer_sequence
		>(
			value_,
			[](
				sge::cg::string const &_string
			)
			{
				return
					_string.c_str();
			}
		)
	};

	result.push_back(
		nullptr
	);

	return
		result;
}

sge::cg::program::compile_options::string_sequence const &
sge::cg::program::compile_options::value() const
{
	return
		value_;
}
