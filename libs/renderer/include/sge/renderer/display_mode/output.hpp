//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DISPLAY_MODE_OUTPUT_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_OUTPUT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

/**
\brief Outputs a display mode

Outputs \a mode to \a stream

\return \a stream
*/
SGE_RENDERER_DETAIL_SYMBOL
fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &stream,
	sge::renderer::display_mode::object const &mode
);

}
}
}

#endif
