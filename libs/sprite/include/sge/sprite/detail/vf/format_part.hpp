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
#include <fcppt/brigand/pair_first.hpp>
#include <fcppt/brigand/pair_second.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/algorithms/flatten.hpp>
#include <brigand/algorithms/remove.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/append.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/pair.hpp>
#include <brigand/types/args.hpp>
#include <brigand/types/no_such_type.hpp>
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
	brigand::list<
		typename
		sge::sprite::detail::vf::pos<
			Choices
		>::type
	>
	basic;

	template<
		typename Container
	>
	struct point_size_extra
	{
		typedef
		brigand::append<
			basic,
			brigand::list<
				typename
				sge::sprite::detail::vf::point_size<
					Choices
				>::type
			>
		>
		type;
	};

	typedef
	typename
	brigand::eval_if<
		sge::sprite::config::is_point_size<
			typename Choices::size_choice
		>,
		point_size_extra<
			basic
		>,
		brigand::identity<
			basic
		>
	>::type
	basic_with_size;

	template<
		typename Type
	>
	struct make_vector
	{
		typedef
		brigand::list<
			typename Type::type
		>
		type;
	};

	typedef
	brigand::list<
		brigand::pair<
			brigand::bind<
				sge::sprite::config::is_with_color,
				brigand::_1
			>,
			make_vector<
				sge::sprite::detail::vf::color<
					Choices
				>
			>
		>,
		brigand::pair<
			brigand::bind<
				sge::sprite::config::is_with_texture,
				brigand::_1
			>,
			sge::sprite::detail::vf::texpos<
				Choices
			>
		>,
		brigand::pair<
			brigand::bind<
				sge::sprite::config::is_with_texture_point_size,
				brigand::_1
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
	struct get_second
	{
		typedef
		typename
		fcppt::brigand::pair_second<
			Pair
		>::type
		type;
	};

	template<
		typename Pair
	>
	using
	make_element
	=
	typename
	brigand::eval_if<
		brigand::found<
			typename
			Choices::optional_elements,
			fcppt::brigand::pair_first<
				Pair
			>
		>,
		get_second<
			Pair
		>,
		brigand::identity<
			brigand::no_such_type_
		>
	>::type;
public:
	typedef
	sge::renderer::vf::part<
		brigand::append<
			basic_with_size,
			brigand::flatten<
				brigand::remove<
					brigand::transform<
						optional_primitives,
						brigand::bind<
							make_element,
							brigand::_1
						>
					>,
					brigand::no_such_type_
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
