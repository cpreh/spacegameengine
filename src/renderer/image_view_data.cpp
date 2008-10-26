/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/image_view_data.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

namespace
{

template<
	typename Dst
>
struct image_view_data_fn {
	typedef void result_type;
	Dst &_dst;

	explicit image_view_data_fn(
		Dst& dst)
	:
		_dst(dst)
	{}

	template<typename Src>
	void operator()(
		Src const &src) const
	{
		_dst = reinterpret_cast<Dst>(
			boost::gil::interleaved_view_get_raw_data(src));
	}
};

template<
	typename T,
	typename Dst
>
void variant_data_fn(
	boost::gil::variant<T> const &src,
	Dst &dst)
{
	image_view_data_fn<Dst> fn(dst);
	boost::gil::apply_operation(src, fn);
}

}

unsigned char *
sge::renderer::image_view_data(
	image_view const &v)
{
	unsigned char *ret(0);
	variant_data_fn(v, ret);
	return ret;
}

unsigned char const *
sge::renderer::image_view_data(
	const_image_view const &v)
{
	unsigned char const *ret(0);
	variant_data_fn(v, ret);
	return ret;
}
