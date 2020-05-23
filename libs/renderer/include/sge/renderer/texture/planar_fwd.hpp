//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_PLANAR_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_PLANAR_FWD_HPP_INCLUDED

#include <sge/image2d/tag.hpp>
#include <sge/renderer/texture/basic_lockable_box_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

using
planar
=
sge::renderer::texture::basic_lockable_box<
	sge::image2d::tag
>;

}
}
}

#endif
