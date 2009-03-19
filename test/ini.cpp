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


#include <sge/parse/ini/parse.hpp>
#include <boost/foreach.hpp>
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
		"[blabla]\nfoo = 42\nconfuse=5\nbar=3.4\nimagepath=/tmp/test\n"
		"[section2]\nblubb=bar\n"
	);

	std::string::const_iterator beg(
		test.begin()
	);

	sge::parse::ini::section_vector result;

	if(!sge::parse::ini::parse(
		beg,
		test.end(),
		result
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
		std::cout << '[' << section.header << "]\n";

		BOOST_FOREACH(
			sge::parse::ini::entry_vector::const_reference entry,
			section.entries
		)
			std::cout
				<< entry.name
				<< " = "
				<< entry.value
				<< '\n';

		std::cout << '\n';
	}
}
