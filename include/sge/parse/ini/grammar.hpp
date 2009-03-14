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


#ifndef SGE_PARSE_INI_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_INI_GRAMMAR_HPP_INCLUDED

#include <sge/parse/ini/detail/adapt_entry.hpp>
#include <sge/parse/ini/detail/adapt_section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/string.hpp>

// TODO: include only the headers which are needed!
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace sge
{
namespace parse
{
namespace ini
{

template<
	typename In
>
struct grammar
:
boost::spirit::qi::grammar<
	In,
	section_vector(),
	boost::spirit::ascii::space_type
> {
	typedef boost::spirit::ascii::space_type space_type;

	grammar()
	:
		grammar::base_type(
			ini_
		)
	{
		using boost::spirit::char_;
		using boost::spirit::int_;
		using boost::spirit::double_;
		using boost::spirit::lexeme;

		value_ %= int_ | double_ | (+char_);
		entry_ %= (+char_ - char_('=')) >> char_('=') >> value_;
		header_ %= lexeme['[' >> +(char_ - ']') >> ']'];
		section_ %= header_ >> *entry_;
		ini_ %= *section_;
	}
private:
	boost::spirit::qi::rule<
		In,
		value(),
		space_type
	> value_;

	boost::spirit::qi::rule<
		In,
		entry(),
		space_type
	> entry_;

	boost::spirit::qi::rule<
		In,
		string(),
		space_type
	> header_;

	boost::spirit::qi::rule	<
		In,
		section(),
		space_type
	> section_;

	boost::spirit::qi::rule<
		In,
		section_vector(),
		space_type
	> ini_;
};

}
}
}

#endif
