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


#include <sge/renderer/color_converted_image_view.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/detail/fold_color_format.hpp>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp>

namespace
{

template<
	typename View
>
struct operation {
	typedef View const result_type;

	explicit operation(
		View const &v);

	template<
		typename T
	>
	View const operator()() const;
private:
	View const v;
};

}

sge::renderer::const_image_view const
sge::renderer::color_converted_image_view(
	image_view const &view,
	color_format::type const fmt)
{
	return color_converted_image_view(
		make_const_image_view(
			view),
		fmt);
}

sge::renderer::const_image_view const
sge::renderer::color_converted_image_view(
	const_image_view const &view,
	color_format::type const fmt)
{
	return fold_color_format(
		operation<const_image_view>(
			view),
		fmt);
}

namespace
{

template<
	typename View
>
operation<View>::operation(
	View const &v)
:
	v(v)
{}

template<
	typename View
>
template<
	typename T
>
View const
operation<View>::operator()() const
{
	return View(
		boost::gil::color_converted_view<
			T>(
				v));
}

}
