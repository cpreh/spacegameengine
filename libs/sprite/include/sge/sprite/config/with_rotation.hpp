//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_WITH_ROTATION_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_ROTATION_HPP_INCLUDED

#include <sge/sprite/config/with_rotation_fwd.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/types/rotation.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>


namespace sge::sprite::config
{

struct with_rotation
{
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
				sge::sprite::roles::rotation,
				sge::sprite::types::rotation<
					typename
					Choices::type_choices
				>
			>
		>;
	};
};

}

#endif
