//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_TYPES_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED
#define SGE_SPRITE_TYPES_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED

#include <sge/sprite/types/dim_fwd.hpp>
#include <sge/sprite/types/texture_size_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace sprite
{
namespace types
{

template<
	typename TypeChoices
>
using
size_or_texture_size
=
fcppt::variant::object<
	sge::sprite::types::dim<
		TypeChoices
	>,
	sge::sprite::types::texture_size
>;

}
}
}

#endif
