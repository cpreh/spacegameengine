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


#include <sge/image/view/data.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <mizuiro/image/is_raw_view.hpp>
#include <boost/utility/enable_if.hpp>

namespace
{

template<
	typename Dst
>
class visitor {
public:
	typedef Dst result_type;

	template<
		typename Src
	>
	typename boost::disable_if<
		mizuiro::image::is_raw_view<
			Src
		>,
		result_type
	>::type
	operator()(
		Src const &src
	) const
	{
		// casting to a byte buffer is ok
		return reinterpret_cast<
			Dst
		>(
			src.data()
		);
	}

	template<
		typename Src
	>
	typename boost::enable_if<
		mizuiro::image::is_raw_view<
			Src
		>,
		result_type
	>::type
	operator()(
		Src const &src
	) const
	{
		return src.data().get();
	}
};

template<
	typename Dest,
	typename View
>
Dest
data_impl(
	View const &v)
{
	return fcppt::variant::apply_unary(
		visitor<Dest>(),
		v
	);
}

}

sge::image::raw_pointer
sge::image::view::data(
	object const &v)
{
	return data_impl<
		raw_pointer
	>(
		v
	);
}

sge::image::const_raw_pointer
sge::image::view::data(
	const_object const &v)
{
	return data_impl<
		const_raw_pointer
	>(
		v
	);
}
