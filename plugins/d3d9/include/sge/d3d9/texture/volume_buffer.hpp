//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_VOLUME_BUFFER_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_VOLUME_BUFFER_HPP_INCLUDED

#include <sge/d3d9/texture/basic_buffer_fwd.hpp>
#include <sge/d3d9/texture/volume_types_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

typedef sge::d3d9::texture::basic_buffer<
	sge::d3d9::texture::volume_types
> volume_buffer;

}
}
}

#endif
