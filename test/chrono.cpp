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


#include <sge/chrono/chrono.hpp>
#include <iostream>
#include <ostream>
#include <cmath>

int main()
{
	sge::chrono::system_clock::time_point const tp(
		sge::chrono::system_clock::now()
	);

	typedef
	sge::chrono::time_point<
		sge::chrono::system_clock,
		sge::chrono::seconds
	> other_time;

	other_time const ot(
		sge::chrono::time_point_cast<
			other_time::duration
		>(
			tp
		)
	);

	std::cout << ot << '\n';

	std::cout
		<< sge::chrono::time_point_cast<
			sge::chrono::days
		>(
			ot
		)
		<< '\n';
	
	// measure some time:
	
	typedef sge::chrono::high_resolution_clock::time_point hrc_tp;

	hrc_tp const begin(
		sge::chrono::high_resolution_clock::now()
	);

	for(
		unsigned i = 0;
		i < 100;
		++i
	)
		std::cout
			<< std::sqrt(
				static_cast<
					float
				>(
					i
				)
			)
			<< ' ';
	
	hrc_tp const end(
		sge::chrono::high_resolution_clock::now()
	);

	hrc_tp::duration const time_taken(
		end - begin
	);

	std::cout
		<< "\ntime taken: "
		<< time_taken
		<< " (in units of "
		<< hrc_tp::period::num
		<< '/'
		<< hrc_tp::period::den
		<< "), in seconds: "
		<< sge::chrono::duration_cast<
			sge::chrono::duration<
				double
			>
		>(
			time_taken
		)
		<< '\n';
}
