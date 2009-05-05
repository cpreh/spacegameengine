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



#include <sge/random/uniform.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/random/last_exclusive_range.hpp>
#include <sge/random/actor/normalized.hpp>
#include <sge/random/actor/element.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/cerr.hpp>
#include <sge/cout.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

namespace
{

template<
	typename Rng
>
void print_values(
	Rng &rng)
{
	for(unsigned i = 0; i < 100; ++i)
		sge::cout << rng() << SGE_TEXT(' ');
	sge::cout << SGE_TEXT('\n');
}

void test_function()
{
	sge::cout << SGE_TEXT("test\n");
}

}

int main()
try
{
	sge::random::uniform<int> rng(
		sge::random::inclusive_range<int>(
			0,
			10
		)
	);

	print_values(rng);

	sge::random::uniform<float> rngf(
		sge::random::inclusive_range<float>(
			0.f,
			10.f
		)
	);
	
	print_values(rngf);
	
	sge::random::uniform<int> rngex(
		sge::random::last_exclusive_range<int>(
			0,
			10
		)
	);

	sge::random::actor::normalized actor(
		sge::assign::make_container<
			sge::random::actor::container
		>(
			sge::random::actor::element(
				1.,
				test_function
			)
		)
	);

	print_values(rngex);

	actor();
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}
