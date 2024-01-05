//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_MUXING_STREAMBUF_FWD_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_STREAMBUF_FWD_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::console
{

template <typename Char, typename Traits = std::char_traits<Char>>
class muxing_streambuf; // IWYU pragma: export

}

#endif
