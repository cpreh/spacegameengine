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


#include <sge/image2d/algorithm/print.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/nonassignable.hpp>
#include <mizuiro/image/algorithm/print.hpp>

namespace
{

class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	)
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
sge::image2d::algorithm::print(
	fcppt::io::ostream &_ostream,
	view::const_object const &_view
)
{
	fcppt::variant::apply_unary(
		::visitor(
			_ostream
		),
		_view
	);
}

namespace
{

visitor::visitor(
	fcppt::io::ostream &_ostream
)
:
	ostream_(_ostream)
{}

template<
	typename View
>
visitor::result_type
visitor::operator()(
	View const &_view
) const
{
	mizuiro::image::algorithm::print(
		ostream_,
		_view
	);
}

}
