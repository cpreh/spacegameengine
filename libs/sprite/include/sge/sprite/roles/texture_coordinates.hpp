//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_ROLES_TEXTURE_COORDINATES_HPP_INCLUDED
#define SGE_SPRITE_ROLES_TEXTURE_COORDINATES_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <fcppt/record/make_label_arg.hpp>


namespace sge
{
namespace sprite
{
namespace roles
{

FCPPT_RECORD_MAKE_LABEL_ARG(
	texture_coordinates,
	sge::sprite::texture_level
);

}
}
}

#endif
