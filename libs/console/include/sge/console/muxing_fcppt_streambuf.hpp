//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_MUXING_FCPPT_STREAMBUF_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_FCPPT_STREAMBUF_HPP_INCLUDED

#include <sge/console/muxing_narrow_streambuf.hpp>
#include <sge/console/muxing_streambuf.hpp>
#include <sge/console/muxing_wide_streambuf.hpp>
#include <fcppt/char_type.hpp>


namespace sge::console
{

using
muxing_fcppt_streambuf
=
sge::console::muxing_streambuf<
	fcppt::char_type
>;

}

#endif
