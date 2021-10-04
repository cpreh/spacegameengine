//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_LOG_LOCATION_HPP_INCLUDED
#define SGE_PLUGIN_LOG_LOCATION_HPP_INCLUDED

#include <sge/plugin/detail/symbol.hpp>
#include <fcppt/log/location.hpp>


namespace sge::plugin
{

SGE_PLUGIN_DETAIL_SYMBOL
fcppt::log::location
log_location();

}

#endif
