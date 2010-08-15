/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/algorithm/fill.hpp>
#include <sge/image/color/any/convert.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <mizuiro/image/algorithm/fill_c.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <mizuiro/color/object_impl.hpp>

namespace
{

class fill_visitor {
public:
	typedef void result_type;

	explicit fill_visitor(
		sge::image::color::any::object const &col
	);

	template<
		typename T
	>
	result_type
	operator()(
		T const &) const;
private:
	sge::image::color::any::object const col;
};

}

void
sge::image::algorithm::fill(
	view::object const &dest,
	color::any::object const &c
)
{
	fcppt::variant::apply_unary(
		fill_visitor(
			c
		),
		dest
	);
}

namespace
{

fill_visitor::fill_visitor(
	sge::image::color::any::object const &col
)
:
	col(col)
{}

template<
	typename T
>
fill_visitor::result_type
fill_visitor::operator()(
	T const &view
) const
{
	return mizuiro::image::algorithm::fill_c(
		view,
		sge::image::color::any::convert<
			typename T::color_format
		>(
			col
		)
	);
}

}
