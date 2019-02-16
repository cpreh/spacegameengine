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


#ifndef SGE_PARSE_IMPL_PARSE_STRING_HPP_INCLUDED
#define SGE_PARSE_IMPL_PARSE_STRING_HPP_INCLUDED

#include <fcppt/parse/grammar.hpp>
#include <fcppt/parse/parse_string.hpp>
#include <fcppt/parse/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace impl
{

template<
	typename Result,
	typename Ch,
	typename Skipper
>
fcppt::parse::result<
	Ch,
	Result
>
parse_string(
	std::basic_string<
		Ch
	> &&_string,
	fcppt::parse::grammar<
		Result,
		Ch,
		Skipper
	> const &_grammar
)
{
	return
		fcppt::parse::parse_string(
			*_grammar.start(),
			std::move(
				_string
			),
			_grammar.skipper()
		);
}

}
}
}

#endif
