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


#ifndef SGE_IMAGE_STORE_BASIC_HPP_INCLUDED
#define SGE_IMAGE_STORE_BASIC_HPP_INCLUDED

#include <sge/image/basic_dim_fwd.hpp>
#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/pixel/mizuiro_type_fwd.hpp>
#include <sge/image/store/basic_fwd.hpp>
#include <sge/image/view/mizuiro_access.hpp>
#include <sge/image/view/mizuiro_traits.hpp>
#include <sge/image/view/to_wrapped_type.hpp>
#include <mizuiro/image/store_decl.hpp>
#include <fcppt/no_init_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace image
{
namespace store
{

template<
	typename Format
>
class basic
{
public:
	typedef
	mizuiro::image::store<
		Format,
		sge::image::view::mizuiro_access
	>
	internal_type;

	typedef
	typename
	internal_type::pointer
	pointer;

	typedef
	typename
	internal_type::const_pointer
	const_pointer;

	typedef
	sge::image::basic_dim<
		Format::dim::static_size
	>
	dim;

	typedef
	typename
	internal_type::view_type
	view_type;

	typedef
	typename
	internal_type::const_view_type
	const_view_type;

	typedef
	sge::image::view::to_wrapped_type<
		view_type
	>
	wrapped_view_type;

	typedef
	sge::image::view::to_wrapped_type<
		const_view_type
	>
	const_wrapped_view_type;

	typedef
	sge::image::pixel::mizuiro_type<
		typename
		Format::color_format
	>
	mizuiro_color;

	typedef
	fcppt::function<
		void (
			view_type const &
		)
	>
	init_function;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	explicit
	basic(
		internal_type &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic(
		dim const &,
		fcppt::no_init const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic(
		dim const &,
		mizuiro_color const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic(
		dim const &,
		init_function const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic(
		basic const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic(
		basic &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic &
	operator=(
		basic const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic &
	operator=(
		basic &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~basic();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	pointer
	data();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_pointer
	data() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	view_type
	view();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_view_type
	view() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	wrapped_view_type
	wrapped_view();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_wrapped_view_type
	wrapped_view() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_wrapped_view_type
	const_wrapped_view() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	dim
	size() const;
private:
	internal_type internal_;
};

}
}
}

#endif
