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


#ifndef SGE_PARSE_JSON_OUTPUT_TO_RANGE_HPP_INCLUDED
#define SGE_PARSE_JSON_OUTPUT_TO_RANGE_HPP_INCLUDED

#//include <sge/parse/json/object.hpp>
//#include <sge/parse/json/output/grammar.hpp>
#include <sge/parse/json/output/tabbed_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
//#include <boost/spirit/include/karma_generate.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace output
{

template<
	typename Out
>
bool
to_range(
	Out &_beg,
	json::object const &_data
)
{
	fcppt::string const result(
		sge::parse::json::output::tabbed_to_string(
			_data
		)
	);

	std::copy(
		result.begin(),
		result.end(),
		_beg
	);

	return true;
/*
	output::grammar<
		Out
	> parser;

	return
		boost::spirit::karma::generate(
			beg,
			parser,
			data
		);*/
}

}
}
}
}

#endif
