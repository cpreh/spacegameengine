//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_IS_TYPE_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_IS_TYPE_CHOICES_HPP_INCLUDED

#include <sge/sprite/config/type_choices_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	typename T
>
struct is_type_choices
:
std::false_type
{
};

template<
	typename Unit,
	typename Float
>
struct is_type_choices<
	sge::sprite::config::type_choices<
		Unit,
		Float
	>
>
:
std::true_type
{
};

}
}
}

#endif
