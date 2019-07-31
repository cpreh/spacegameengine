//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_ATLASING_MAKE_INNER_RECT_HPP_INCLUDED
#define SGE_TEXTURE_ATLASING_MAKE_INNER_RECT_HPP_INCLUDED

#include <sge/texture/atlasing/inner_rect_fwd.hpp>
#include <sge/texture/atlasing/outer_rect_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>


namespace sge
{
namespace texture
{
namespace atlasing
{

SGE_TEXTURE_DETAIL_SYMBOL
sge::texture::atlasing::inner_rect
make_inner_rect(
	sge::texture::atlasing::outer_rect const &
);

}
}
}

#endif
