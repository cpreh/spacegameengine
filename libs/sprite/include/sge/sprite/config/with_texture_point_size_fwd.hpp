//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_WITH_TEXTURE_POINT_SIZE_FWD_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_TEXTURE_POINT_SIZE_FWD_HPP_INCLUDED

#include <sge/sprite/config/texture_ownership_fwd.hpp>


namespace sge::sprite::config
{

template<
	typename TextureLevels,
	typename PosOptions,
	typename SizeOptions,
	sge::sprite::config::texture_ownership
>
struct with_texture_point_size;

}

#endif
