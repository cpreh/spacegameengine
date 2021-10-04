//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_RENDER_TEXTURE_REF_FWD_HPP_INCLUDED
#define SGE_SPRITE_RENDER_TEXTURE_REF_FWD_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge::sprite::render
{

using
texture_ref
=
fcppt::reference<
	sge::renderer::texture::planar const
>;

}

#endif
