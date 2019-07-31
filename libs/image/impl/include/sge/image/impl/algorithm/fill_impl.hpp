//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_ALGORITHM_FILL_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_FILL_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/algorithm/fill.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <sge/image/pixel/convert.hpp>
#include <sge/image/pixel/object_fwd.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <mizuiro/image/algorithm/fill_c.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename Tag
>
void
sge::image::algorithm::fill(
	sge::image::view::object<
		Tag
	> const &_view,
	sge::image::pixel::object<
		sge::image::traits::image::color_tag<
			Tag
		>
	> const &_value,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	fcppt::variant::apply(
		[
			&_value,
			_uninitialized
		](
			auto const &_view_inner
		)
		{
			mizuiro::image::algorithm::fill_c(
				_view_inner,
				sge::image::pixel::convert<
					sge::image::traits::image::color_tag<
						Tag
					>,
					typename
					std::decay<
						decltype(
							_view_inner
						)
					>::type::format::color_format
				>(
					_value
				),
				sge::image::impl::algorithm::convert_uninitialized(
					_uninitialized
				)
			);
		},
		_view.get()
	);
}

#endif
