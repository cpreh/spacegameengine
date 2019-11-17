//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <sge/sprite/config/is_point_size.hpp>
#include <sge/sprite/config/is_with_color.hpp>
#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/config/is_with_texture_point_size.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/detail/vf/color.hpp>
#include <sge/sprite/detail/vf/point_size.hpp>
#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/detail/vf/texpos.hpp>
#include <sge/sprite/detail/vf/texture_point.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/invoke.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/lambda/trait.hpp>
#include <metal/list/contains.hpp>
#include <metal/list/flatten.hpp>
#include <metal/list/join.hpp>
#include <metal/list/list.hpp>
#include <metal/list/remove.hpp>
#include <metal/list/transform.hpp>
#include <metal/number/if.hpp>
#include <metal/pair/first.hpp>
#include <metal/pair/pair.hpp>
#include <metal/pair/second.hpp>
#include <type_traits>
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

	template<
		typename Container
	>
	using
	point_size_extra
	=
	metal::join<
		Container,
		metal::list<
			typename
			sge::sprite::detail::vf::point_size<
				Choices
			>::type
		>
	>;

	typedef
	metal::invoke<
		std::conditional_t<
			sge::sprite::config::is_point_size<
				typename Choices::size_choice
			>::value,
			metal::bind<
				metal::lambda<
					point_size_extra
				>,
				metal::always<
					basic
				>
			>,
			metal::always<
				basic
			>
		>
	>
	basic_with_size;

	template<
		typename Type
	>
	using
	make_vector
	=
	metal::list<
		typename Type::type
	>;

	typedef
	metal::list<
		metal::pair<
			metal::trait<
				sge::sprite::config::is_with_color
			>,
			make_vector<
				sge::sprite::detail::vf::color<
					Choices
				>
			>
		>,
		metal::pair<
			metal::trait<
				sge::sprite::config::is_with_texture
			>,
			sge::sprite::detail::vf::texpos<
				Choices
			>
		>,
		metal::pair<
			metal::trait<
				sge::sprite::config::is_with_texture_point_size
			>,
			sge::sprite::detail::vf::texture_point<
				Choices
			>
		>
	>
	optional_primitives;

	// TODO
	template<
		typename Pair
	>
	using
	make_element
	=
	metal::invoke<
		metal::if_<
			metal::contains<
				typename
				Choices::optional_elements,
				metal::first<
					Pair
				>
			>
		>,
		metal::lambda<
			metal::second
		>,
		metal::always<
			metal::nil
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
