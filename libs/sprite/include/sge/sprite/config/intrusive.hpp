//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_INTRUSIVE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_INTRUSIVE_HPP_INCLUDED

#include <sge/sprite/config/intrusive_fwd.hpp>
#include <sge/sprite/intrusive/connection_ref.hpp>
#include <sge/sprite/roles/connection.hpp>
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

struct intrusive
{
	template<
		typename Choices
	>
	struct apply
	{
		typedef
		metal::list<
			fcppt::record::element<
				sge::sprite::roles::connection,
				sge::sprite::intrusive::connection_ref<
					Choices
				>
			>
		>
		type;
	};
};

}
}
}

#endif
