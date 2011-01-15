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


#include <fcppt/math/matrix/matrix.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/vector/vector.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>
#include <limits>
#include <iosfwd>
#include <numeric>
#include <functional>

int main()
{
	typedef double value_type;

	fcppt::math::matrix::static_<
		value_type,
		3,
		3
	>::type const cie(
		0.49, 0.31, 0.2,
		0.177, 0.83, 0.011,
		0, 0.01, 0.99
	);

	typedef fcppt::math::vector::static_<
		value_type,
		3
	>::type vector_type;

	vector_type in;

	while(!(fcppt::io::cin >> in))
	{
		fcppt::io::cerr << FCPPT_TEXT("Invalid input\n");
		fcppt::io::cin.clear();
		fcppt::io::cin.ignore(
			std::numeric_limits<std::streamsize>::max(),
			FCPPT_TEXT('\n')
		);
	}

	vector_type const cie_vec = cie * in;

	fcppt::io::cout
		<< FCPPT_TEXT("vector in cie space: ")
		<< cie_vec
		<< FCPPT_TEXT('\n');

	value_type const norm(
		std::accumulate(
			cie_vec.begin(),
			cie_vec.end(),
			static_cast<value_type>(0),
			std::plus<value_type>()
		)
	);

	fcppt::io::cout
		<< FCPPT_TEXT("vector in normalized cie space: ")
		<< cie_vec / norm
		<< FCPPT_TEXT('\n');
}
