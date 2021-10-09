//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_BASIC_VECTOR_FWD_HPP_INCLUDED
#define SGE_RENDERER_BASIC_VECTOR_FWD_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>

namespace sge::renderer
{

/**
\brief Typedef helper for renderer::vector2, renderer::vector3 and
renderer::vector4

\ingroup sge_renderer

Creates a vector with value type renderer::scalar.

\tparam Size The dimension to use
*/
template <fcppt::math::size_type Size>
using basic_vector = fcppt::math::vector::static_<sge::renderer::scalar, Size>;

}

#endif
