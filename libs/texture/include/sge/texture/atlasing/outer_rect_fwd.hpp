//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_ATLASING_OUTER_RECT_FWD_HPP_INCLUDED
#define SGE_TEXTURE_ATLASING_OUTER_RECT_FWD_HPP_INCLUDED

#include <sge/renderer/lock_rect_fwd.hpp>
#include <fcppt/declare_strong_typedef.hpp>


namespace sge::texture::atlasing
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sge::renderer::lock_rect,
	outer_rect
);

}

#endif
