//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_IS_TEXTURE_LEVEL_COUNT_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_IS_TEXTURE_LEVEL_COUNT_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
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
struct is_texture_level_count
:
std::false_type
{
};

template<
	sge::sprite::texture_level Count
>
struct is_texture_level_count<
	sge::sprite::config::texture_level_count<
		Count
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
