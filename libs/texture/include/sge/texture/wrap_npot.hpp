//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_WRAP_NPOT_HPP_INCLUDED
#define SGE_TEXTURE_WRAP_NPOT_HPP_INCLUDED

#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/detail/symbol.hpp>


namespace sge::texture
{

SGE_TEXTURE_DETAIL_SYMBOL
sge::texture::part_unique_ptr
wrap_npot(
	sge::renderer::device::core_ref,
	sge::renderer::texture::planar_parameters const &
);

}

#endif
