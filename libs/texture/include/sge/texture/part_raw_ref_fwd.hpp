//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_PART_RAW_REF_FWD_HPP_INCLUDED
#define SGE_TEXTURE_PART_RAW_REF_FWD_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/basic_part_raw_fwd.hpp>


namespace sge
{
namespace texture
{

typedef sge::texture::basic_part_raw<
	sge::renderer::texture::planar &
> part_raw_ref;

}
}

#endif
