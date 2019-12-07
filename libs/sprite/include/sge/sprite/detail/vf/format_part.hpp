//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <sge/sprite/config/is_with_color.hpp>
#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/config/is_with_texture_point_size.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/detail/vf/color_types.hpp>
#include <sge/sprite/detail/vf/point_size_extra.hpp>
#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/detail/vf/texpos.hpp>
#include <sge/sprite/detail/vf/texture_point.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace vf
{

template<
	typename Choices
>
struct format_part
{
private:
	typedef
	metal::list<
		typename
		sge::sprite::detail::vf::pos<
			Choices
		>::type
	>
	basic;

	typedef
	metal::join<
		basic,
		typename
		sge::sprite::detail::vf::point_size_extra<
			Choices
		>::type
	>
	basic_with_size;

	typedef
	metal::list<
		metal::pair<
			metal::trait<
				sge::sprite::config::is_with_color
			>,
			metal::bind<
				metal::lambda<
					sge::sprite::detail::vf::color_types
				>,
				metal::always<
					Choices
				>
			>
		>,
		metal::pair<
			metal::trait<
				sge::sprite::config::is_with_texture
			>,
			metal::bind<
				metal::lambda<
					sge::sprite::detail::vf::texpos
				>,
				metal::always<
					Choices
				>
			>
		>,
		metal::pair<
			metal::trait<
				sge::sprite::config::is_with_texture_point_size
			>,
			metal::bind<
				metal::lambda<
					sge::sprite::detail::vf::texture_point
				>,
				metal::always<
					Choices
				>
			>
		>
	>
	optional_primitives;

	template<
		typename Pair
	>
	using
	make_element
	=
	metal::invoke<
		metal::if_<
			metal::any_of<
				typename
				Choices::optional_elements,
				metal::first<
					Pair
				>
			>,
			metal::second<
				Pair
			>,
			metal::always<
				metal::nil
			>
		>
	>;
public:
	typedef
	sge::renderer::vf::part<
		metal::join<
			basic_with_size,
			metal::flatten<
				metal::remove<
					metal::transform<
						metal::lambda<
							make_element
						>,
						optional_primitives
					>,
					metal::nil
				>
			>
		>
	>
	type;
};

}
}
}
}

#endif
