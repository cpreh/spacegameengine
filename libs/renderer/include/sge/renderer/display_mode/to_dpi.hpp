//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DISPLAY_MODE_TO_DPI_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_TO_DPI_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/dpi_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::display_mode::dpi
to_dpi(
	sge::renderer::display_mode::optional_object const &
);

}
}
}

#endif
