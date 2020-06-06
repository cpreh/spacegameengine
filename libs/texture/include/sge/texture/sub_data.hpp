//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_SUB_DATA_HPP_INCLUDED
#define SGE_TEXTURE_SUB_DATA_HPP_INCLUDED

#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/pos_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>


namespace sge
{
namespace texture
{

SGE_TEXTURE_DETAIL_SYMBOL
void
sub_data(
	sge::renderer::texture::planar &, // NOLINT(google-runtime-references)
	sge::image2d::view::const_object const &,
	sge::texture::pos const &,
	sge::image::algorithm::uninitialized
);

}
}

#endif
