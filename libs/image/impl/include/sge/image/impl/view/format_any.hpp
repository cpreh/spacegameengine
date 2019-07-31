//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_FORMAT_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_FORMAT_ANY_HPP_INCLUDED

#include <sge/image/impl/static_to_dynamic_format.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <fcppt/use.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace view
{

template<
	typename ColorTag,
	typename View
>
sge::image::traits::pixel::format<
	ColorTag
>
format_any(
	View const &_view
)
{
	return
		fcppt::variant::apply(
			[](
				auto const &_src
			)
			{
				FCPPT_USE(
					_src
				);

				return
					sge::image::impl::static_to_dynamic_format<
						ColorTag,
						typename
						std::decay<
							decltype(
								_src
							)
						>::type::format::color_format
					>::value;
			},
			_view.get()
		);
}

}
}
}
}

#endif
