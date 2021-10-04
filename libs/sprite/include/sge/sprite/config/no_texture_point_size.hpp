//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_NO_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_NO_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/config/no_texture_point_size_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::config
{

struct no_texture_point_size
{
	using
	is_texture_point_size
	=
	std::true_type;
};

}

#endif
