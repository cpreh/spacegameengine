/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/parse/ini/parse_range.hpp>
#include <sge/string.hpp>
#include <sge/cout.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <cstdlib>

int main()
{
	sge::string const test(
		FCPPT_TEXT("[blabla]\nfoo = 42\nconfuse=5\nbar=3.4\nimagepath=/tmp/test\n")
		FCPPT_TEXT("[section2]\nblubb=bar\n")
	);

	sge::string::const_iterator beg(
		test.begin()
	);

	sge::parse::ini::section_vector result;

	if(!sge::parse::ini::parse_range(
		beg,
		test.end(),
		result
	))
	{
		sge::cerr << FCPPT_TEXT("failure\n");
		return EXIT_FAILURE;
	}

	BOOST_FOREACH(
		sge::parse::ini::section_vector::const_reference section,
		result
	)
	{
		sge::cout << FCPPT_TEXT('[') << section.header << SGE_TEXT("]\n");

		BOOST_FOREACH(
			sge::parse::ini::entry_vector::const_reference entry,
			section.entries
		)
			sge::cout
				<< entry.name
				<< FCPPT_TEXT(" = ")
				<< entry.value
				<< FCPPT_TEXT('\n');

		sge::cout << FCPPT_TEXT('\n');
	}
}
