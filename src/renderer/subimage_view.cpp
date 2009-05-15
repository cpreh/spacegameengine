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



#include <sge/renderer/subimage_view.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <boost/gil/image_view_factory.hpp>

namespace
{

template<
	typename View
>
View const
subimage_view_impl(
	View const &,
	sge::renderer::lock_rect const &);

template<
	typename Result
>
class visitor {
public:
	typedef Result result_type;

	explicit visitor(
		sge::renderer::lock_rect const &);
	
	template<
		typename T
	>
	result_type const
	operator()(
		T const &) const;
private:
	sge::renderer::lock_rect const lr;
};

}

sge::renderer::image_view const
sge::renderer::subimage_view(
	image_view const &src,
	lock_rect const &lr)
{
	return subimage_view_impl(
		src,
		lr
	);
}

sge::renderer::const_image_view const
sge::renderer::subimage_view(
	const_image_view const &src,
	lock_rect const &lr)
{
	return subimage_view_impl(
		src,
		lr
	);
}

namespace
{

template<
	typename View
>
View const
subimage_view_impl(
	View const &v,
	sge::renderer::lock_rect const &r)
{
	return sge::variant::apply_unary(
		visitor<View>(
			r
		),
		v
	);
}

template<
	typename Result
>
visitor<Result>::visitor(
	sge::renderer::lock_rect const &lr)
:
	lr(lr)
{}

template<
	typename Result
>
template<
	typename T
>
typename visitor<Result>::result_type const
visitor<Result>::operator()(
	T const &v) const
{
	return boost::gil::subimage_view(
		v,
		static_cast<int>(lr.left()),
		static_cast<int>(lr.top()),
		static_cast<int>(lr.w()),
		static_cast<int>(lr.h())
	);
}

}
