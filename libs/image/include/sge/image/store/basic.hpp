//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/function_impl.hpp>
#include <fcppt/no_init_fwd.hpp>


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
	using
	internal_type
	=
	mizuiro::image::store<
		Format,
		sge::image::view::mizuiro_access
	>;

	using
	pointer
	=
	typename
	internal_type::pointer;

	using
	const_pointer
	=
	typename
	internal_type::const_pointer;

	using
	dim
	=
	sge::image::basic_dim<
		Format::dim::static_size
	>;

	using
	view_type
	=
	typename
	internal_type::view_type;

	using
	const_view_type
	=
	typename
	internal_type::const_view_type;

	using
	wrapped_view_type
	=
	sge::image::view::to_wrapped_type<
		view_type
	>;

	using
	const_wrapped_view_type
	=
	sge::image::view::to_wrapped_type<
		const_view_type
	>;

	using
	mizuiro_color
	=
	sge::image::pixel::mizuiro_type<
		typename
		Format::color_format
	>;

	using
	init_function
	=
	fcppt::function<
		void (
			view_type const &
		)
	>;

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
	)
	noexcept;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic &
	operator=(
		basic const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	basic &
	operator=(
		basic &&
	)
	noexcept;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~basic();

	[[nodiscard]]
	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	pointer
	data();

	[[nodiscard]]
	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_pointer
	data() const;

	[[nodiscard]]
	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	view_type
	view();

	[[nodiscard]]
	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_view_type
	view() const;

	[[nodiscard]]
	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	wrapped_view_type
	wrapped_view();

	[[nodiscard]]
	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_wrapped_view_type
	wrapped_view() const;

	[[nodiscard]]
	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_wrapped_view_type
	const_wrapped_view() const;

	[[nodiscard]]
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
