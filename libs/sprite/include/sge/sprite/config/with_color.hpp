//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_WITH_COLOR_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_COLOR_HPP_INCLUDED

#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/sprite/config/with_color_fwd.hpp>
#include <sge/sprite/roles/color.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	typename ColorFormat
>
struct with_color
{
	using
	color_format
	=
	ColorFormat;

	template<
		typename Choices
	>
	struct apply
	{
		using
		type
		=
		metal::list<
			fcppt::record::element<
				sge::sprite::roles::color,
				sge::image::pixel::mizuiro_type<
					color_format
				>
			>
		>;
	};
};

}
}
}

#endif
