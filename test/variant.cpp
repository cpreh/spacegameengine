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
#include <sge/variant/apply_binary.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace
{

struct visitor {
	typedef void result_type;

	template<
		typename T1,
		typename T2
	>
	void operator()(
		T1 const &t1,
		T2 const &t2) const
	{
		sge::cerr << t1 << SGE_TEXT(' ') << t2 << SGE_TEXT('\n');
	}
};

}

int main()
try
{
	typedef sge::variant::object<
		boost::mpl::vector2<
			int,
			sge::string
		>
	> variant;

	variant v(
		sge::string(
			SGE_TEXT("blabla")
		)
	);

	variant u(
		42
	);

	sge::variant::apply_binary(
		visitor(),
		v,
		u
	);
}
SGE_MAINLOOP_CATCH_BLOCK
