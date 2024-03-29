//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CAPS_MAX_TEXTURE_SIZE_HPP_INCLUDED
#define SGE_RENDERER_CAPS_MAX_TEXTURE_SIZE_HPP_INCLUDED

#include <sge/renderer/dim2.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::renderer::caps
{

/**
\brief A strong typedef for the maximum 2D texture size

\ingroup sge_renderer
*/
FCPPT_DECLARE_STRONG_TYPEDEF(sge::renderer::dim2, max_texture_size);

}

#endif
