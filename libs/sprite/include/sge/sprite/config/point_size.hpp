//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/config/point_size_fwd.hpp>
#include <sge/sprite/config/size_choice.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <sge/sprite/types/point_size.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	typename Index
>
struct point_size
:
	sge::sprite::config::size_choice
{
public:
	using
	attribute_index
	=
	Index;

	template<
		typename Choices
	>
	struct apply
	{
		using
		type
		=
		fcppt::mpl::list::object<
			fcppt::record::element<
				sge::sprite::roles::point_size,
				sge::sprite::types::point_size<
					typename
					Choices::type_choices
				>
			>
		>;
	};
};

}
}
}

#endif
