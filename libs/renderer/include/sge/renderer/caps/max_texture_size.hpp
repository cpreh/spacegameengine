//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CAPS_MAX_TEXTURE_SIZE_HPP_INCLUDED
#define SGE_RENDERER_CAPS_MAX_TEXTURE_SIZE_HPP_INCLUDED

#include <sge/renderer/dim2.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace renderer
{
namespace caps
{

/**
\brief A strong typedef for the maximum 2D texture size

\ingroup sge_renderer
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::dim2,
	max_texture_size
);

}
}
}

#endif
