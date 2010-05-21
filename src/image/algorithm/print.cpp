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


#include <sge/image/algorithm/print.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <mizuiro/image/algorithm/print.hpp>

namespace
{

class visitor
{
public:
	typedef void result_type;

	explicit visitor(
		fcppt::io::ostream &
	);
	
	template<
		typename View
	>
	result_type
	operator()(
		View const &
	) const;
private:
	fcppt::io::ostream &ostream_;
};

}

void
sge::image::algorithm::print(
	fcppt::io::ostream &ostream_,
	view::const_object const &view_
)
{
	fcppt::variant::apply_unary(
		visitor(
			ostream_
		),
		view_
	);
}

namespace
{

visitor::visitor(
	fcppt::io::ostream &ostream_
)
:
	ostream_(ostream_)
{}

template<
	typename View
>
visitor::result_type
visitor::operator()(
	View const &view_
) const
{
	mizuiro::image::algorithm::print(
		ostream_,
		view_
	);
}

}
