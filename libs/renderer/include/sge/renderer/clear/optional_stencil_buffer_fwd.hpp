//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CLEAR_OPTIONAL_STENCIL_BUFFER_FWD_HPP_INCLUDED
#define SGE_RENDERER_CLEAR_OPTIONAL_STENCIL_BUFFER_FWD_HPP_INCLUDED

#include <sge/renderer/clear/stencil_buffer_value.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace clear
{

/**
\brief Optional stencil buffer clear value

\ingroup sge_renderer
*/
typedef
fcppt::optional::object<
	sge::renderer::clear::stencil_buffer_value
>
optional_stencil_buffer;

}
}
}

#endif
