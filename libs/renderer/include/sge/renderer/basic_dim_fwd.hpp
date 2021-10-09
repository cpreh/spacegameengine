//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_BASIC_DIM_FWD_HPP_INCLUDED
#define SGE_RENDERER_BASIC_DIM_FWD_HPP_INCLUDED

#include <sge/image/basic_dim_fwd.hpp>
#include <fcppt/math/size_type.hpp>

namespace sge::renderer
{

/**
\brief Typedef helper for renderer::dim2 and renderer::dim3

\ingroup sge_renderer

Creates a dimension with value type renderer::size_type.

\tparam Size The dimension to use
*/
template <fcppt::math::size_type Size>
using basic_dim = sge::image::basic_dim<Size>;

}

#endif
