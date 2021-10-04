//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CAPS_DEVICE_OUTPUT_HPP_INCLUDED
#define SGE_RENDERER_CAPS_DEVICE_OUTPUT_HPP_INCLUDED

#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/io/ostream_fwd.hpp>


namespace sge::renderer::caps
{

/**
\brief Prints a caps object to a stream

\ingroup sge_renderer

Prints \a caps to \a stream.

\param stream The stream to print to

\param caps The caps to print

\return \a stream
*/
SGE_RENDERER_DETAIL_SYMBOL
fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &stream,
	sge::renderer::caps::device const &caps
);

}

#endif
