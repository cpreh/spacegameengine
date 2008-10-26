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


#include <sge/renderer/make_const_image_view.hpp>
#include <boost/gil/extension/dynamic_image/algorithm.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

namespace 
{

template <typename Dst>
struct variant_const_assign_fn {
	typedef void result_type;
	Dst &_dst;

	explicit variant_const_assign_fn(
		Dst& dst)
	: 
		_dst(dst)
	{}

	template<typename Src>
	void operator()(
		Src const &src) const 
	{
		typename Src::const_t const_src(src);
		_dst = const_src;
	}
};

template <typename V1, typename V2>
void variant_const_assign(
	boost::gil::variant<V1> const &src, 
	boost::gil::variant<V2>& dst) 
{
	variant_const_assign_fn<boost::gil::variant<V2> > fn(dst);
	boost::gil::apply_operation(src, fn);
} 

}

sge::renderer::const_image_view const
sge::renderer::make_const_image_view(
	image_view const &ncv)
{
	const_image_view cv;
	variant_const_assign(ncv,cv);
	return cv;
}
