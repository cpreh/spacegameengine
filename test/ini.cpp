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


#include <sge/parse/ini/grammar.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>

namespace
{

struct value_visitor : boost::static_visitor<> {
	template<	
		typename T
	>
	void operator()(
		T const &t) const
	{
		std::cout << t;
	}
};

}

int main()
{
	sge::parse::ini::grammar<
		std::string::const_iterator
	> p;

	std::string const test(
		"[blabla]\nfoo = 42\nbar = 3.4\nimagepath = /tmp/test"
	);

	std::string::const_iterator beg(
		test.begin()
	);

	sge::parse::ini::section_vector result;

	if(!boost::spirit::qi::phrase_parse(
		beg,
		test.end(),
		p,
		result,
		boost::spirit::ascii::space
	))
	{
		std::cerr << "failure\n";
		return EXIT_FAILURE;
	}

	BOOST_FOREACH(
		sge::parse::ini::section_vector::const_reference section,
		result
	)
	{
		std::cout << '[' << std::string(section.header.begin(), section.header.end()) << "]\n";

		BOOST_FOREACH(
			sge::parse::ini::entry_vector::const_reference entry,
			section.entries
		)
		{
			std::cout
				<< std::string(entry.name.begin(), entry.name.end())
				<< " = ";

			boost::apply_visitor(
				value_visitor(),
				entry.value_
			);

			std::cout << '\n';
		}
	}
}
