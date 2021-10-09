//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_VF_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_UNSPECIFIED_DIM_HPP_INCLUDED

#include <sge/renderer/vf/extra.hpp>
#include <sge/renderer/vf/vector.hpp>

namespace sge::sprite::detail::vf
{

template <typename Choices>
using point_size = sge::renderer::vf::extra<
    sge::renderer::vf::vector<typename Choices::type_choices::float_type, 1>,
    typename Choices::size_choice::attribute_index>;

}

#endif
