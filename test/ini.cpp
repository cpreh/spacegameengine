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
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>

int main()
{
	sge::parse::ini::grammar<
		std::string::const_iterator
	> p;

	std::string const test(
		"[blabla]\nfoo = 42"
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

	sge::parse::ini::string const s(
		result.at(0).header
	);

	std::cout << std::string(s.begin(), s.end()) << '\n';
	
}
