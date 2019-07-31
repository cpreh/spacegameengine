//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_WITH_TEXTURE_FWD_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_TEXTURE_FWD_HPP_INCLUDED

#include <sge/sprite/config/texture_coordinates_fwd.hpp>
#include <sge/sprite/config/texture_ownership_fwd.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	typename TextureLevels,
	sge::sprite::config::texture_coordinates,
	sge::sprite::config::texture_ownership
>
struct with_texture;

}
}
}

#endif
