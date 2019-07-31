//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_TYPE_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_TYPE_CHOICES_HPP_INCLUDED

#include <sge/sprite/config/float_type_fwd.hpp>
#include <sge/sprite/config/type_choices_fwd.hpp>
#include <sge/sprite/config/unit_type_fwd.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	typename Unit,
	typename Float
>
struct type_choices<
	sge::sprite::config::unit_type<
		Unit
	>,
	sge::sprite::config::float_type<
		Float
	>
>
{
	typedef typename sge::sprite::config::unit_type<
		Unit
	>::type unit_type;

	typedef typename sge::sprite::config::float_type<
		Float
	>::type float_type;
};

}
}
}

#endif
