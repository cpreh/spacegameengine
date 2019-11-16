//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_WITH_DEPTH_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_DEPTH_HPP_INCLUDED

#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/types/depth.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

struct with_depth
{
	template<
		typename Choices
	>
	struct apply
	{
		typedef
		metal::list<
			fcppt::record::element<
				sge::sprite::roles::depth,
				typename
				sge::sprite::types::depth<
					typename
					Choices::type_choices
				>::type
			>
		>
		type;
	};
};

}
}
}

#endif
