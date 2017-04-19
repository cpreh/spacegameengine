/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_STORE_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_STORE_OBJECT_HPP_INCLUDED

#include <sge/image/dim_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/store/elements.hpp>
#include <sge/image/store/object_fwd.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <fcppt/no_init_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace store
{

template<
	typename Tag
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef
	sge::image::store::elements<
		Tag
	>
	store_elements;

	typedef
	fcppt::variant::object<
		store_elements
	>
	variant;

	typedef
	sge::image::dim<
		Tag
	>
	dim;

	typedef
	sge::image::traits::pixel::format<
		sge::image::traits::image::color_tag<
			Tag
		>
	>
	format;

	// TODO: Can we improve this?
	template<
		typename Element
	>
	explicit
	object(
		Element &&_element
	)
	:
		object(
			variant{
				std::forward<
					Element
				>(
					_element
				)
			}
		)
	{
	}

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	explicit
	object(
		variant &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	object(
		format,
		dim const &,
		fcppt::no_init const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	object(
		object &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	object &
	operator=(
		object &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~object();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	variant &
	get();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	variant const &
	get() const;
private:
	variant variant_;
};

}
}
}

#endif
