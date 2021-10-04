//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LOG_DEFAULT_LEVEL_STREAMS_HPP_INCLUDED
#define SGE_LOG_DEFAULT_LEVEL_STREAMS_HPP_INCLUDED

#include <sge/log/detail/symbol.hpp>
#include <fcppt/log/level_stream_array.hpp>


namespace sge::log
{

SGE_LOG_DETAIL_SYMBOL
fcppt::log::level_stream_array
default_level_streams();

}

#endif
