//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_IS_SIZE_CHOICE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_IS_SIZE_CHOICE_HPP_INCLUDED

#include <sge/sprite/config/size_choice.hpp>
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
using is_size_choice
=
std::is_base_of<
	sge::sprite::config::size_choice,
	T
>;

}
}
}

#endif
