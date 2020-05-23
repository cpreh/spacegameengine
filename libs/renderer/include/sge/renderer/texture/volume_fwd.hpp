//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_VOLUME_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_VOLUME_FWD_HPP_INCLUDED

#include <sge/image3d/tag.hpp>
#include <sge/renderer/texture/basic_lockable_box_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

using
volume
=
sge::renderer::texture::basic_lockable_box<
	sge::image3d::tag
>;

}
}
}

#endif
