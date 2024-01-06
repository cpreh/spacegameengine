//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_LINEAR_ATTENUATION_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_LINEAR_ATTENUATION_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::scenic::render_context::light
{
FCPPT_DECLARE_STRONG_TYPEDEF(sge::renderer::scalar, linear_attenuation);
}

#endif
