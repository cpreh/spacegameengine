//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/renderer/vf/part_from_list.hpp>
#include <sge/sprite/config/is_with_color.hpp>
#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/config/is_with_texture_point_size.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/detail/vf/color_types.hpp>
#include <sge/sprite/detail/vf/point_size_extra.hpp>
#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/detail/vf/texpos.hpp>
#include <sge/sprite/detail/vf/texture_point.hpp>
#include <fcppt/mpl/apply.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/if.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/size_type.hpp>
#include <fcppt/mpl/list/any_of.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/mpl/list/from.hpp>
#include <fcppt/mpl/list/join.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/mpl/list/remove.hpp>


namespace sge::sprite::detail::vf
{

template<
	typename Choices
>
struct format_part
{
private:
	using
	basic
	=
	fcppt::mpl::list::object<
		sge::sprite::detail::vf::pos<
			Choices
		>
	>;

	using
	basic_with_size
	=
	fcppt::mpl::list::append<
		basic,
		typename
		sge::sprite::detail::vf::point_size_extra<
			Choices
		>::type
	>;

	template<
		typename First,
		typename Second
	>
	struct condition_component_pair;

	template<
		typename Pair
	>
	using
	condition
	=
	fcppt::mpl::list::at<
		fcppt::mpl::list::from<
			Pair
		>,
		fcppt::mpl::size_type<
			0U
		>
	>;

	template<
		typename Pair
	>
	using
	component
	=
	fcppt::mpl::list::at<
		fcppt::mpl::list::from<
			Pair
		>,
		fcppt::mpl::size_type<
			1U
		>
	>;

	using
	optional_primitives
	=
	fcppt::mpl::list::object<
		condition_component_pair<
			fcppt::mpl::lambda<
				sge::sprite::config::is_with_color
			>,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					sge::sprite::detail::vf::color_types
				>,
				fcppt::mpl::constant<
					Choices
				>
			>
		>,
		condition_component_pair<
			fcppt::mpl::lambda<
				sge::sprite::config::is_with_texture
			>,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					sge::sprite::detail::vf::texpos
				>,
				fcppt::mpl::constant<
					Choices
				>
			>
		>,
		condition_component_pair<
			fcppt::mpl::lambda<
				sge::sprite::config::is_with_texture_point_size
			>,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					sge::sprite::detail::vf::texture_point
				>,
				fcppt::mpl::constant<
					Choices
				>
			>
		>
	>;

	struct nothing
	{
	};

	template<
		typename Pair
	>
	using
	make_element
	=
	fcppt::mpl::apply<
		fcppt::mpl::if_<
			fcppt::mpl::list::any_of<
				typename
				Choices::optional_elements,
				condition<
					Pair
				>
			>,
			component<
				Pair
			>,
			fcppt::mpl::constant<
				nothing
			>
		>
	>;
public:
	using
	type
	=
	sge::renderer::vf::part_from_list<
		fcppt::mpl::list::append<
			basic_with_size,
			fcppt::mpl::list::join<
				fcppt::mpl::list::remove<
					fcppt::mpl::list::map<
						optional_primitives,
						fcppt::mpl::lambda<
							make_element
						>
					>,
					nothing
				>
			>
		>
	>;
};

}

#endif
