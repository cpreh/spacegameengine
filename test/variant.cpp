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


#include <sge/variant/object_impl.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <boost/mpl/vector.hpp>

int main()
try
{
	typedef sge::variant::object<
		boost::mpl::vector<
			int,
			sge::string
		>
	> variant;

	variant v(
		sge::string(
			SGE_TEXT("blabla")
		)
	);

	sge::cerr << v.get<sge::string>() << SGE_TEXT('\n');
}
SGE_MAINLOOP_CATCH_BLOCK
