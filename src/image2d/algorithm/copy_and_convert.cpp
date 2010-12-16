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


#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <mizuiro/image/algorithm/copy_and_convert.hpp>

namespace
{

class visitor
{
public:
	typedef void result_type;

	template<
		typename Src,
		typename Dest
	>
	result_type
	operator()(
		Src const &,
		Dest const &
	) const;
};

}

void
sge::image2d::algorithm::copy_and_convert(
	view::const_object const &_src,
	view::object const &_dest
)
{
	fcppt::variant::apply_binary(
		visitor(),
		_src,
		_dest
	);
}

namespace
{


template<
	typename Src,
	typename Dest
>
visitor::result_type
visitor::operator()(
	Src const &_src,
	Dest const &_dest
) const
{
	return
		mizuiro::image::algorithm::copy_and_convert(
			_src,
			_dest
		);
}

}
