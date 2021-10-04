//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_FUNCTION_MAP_HPP_INCLUDED
#define SGE_CONSOLE_FUNCTION_MAP_HPP_INCLUDED

#include <sge/console/function.hpp>
#include <sge/font/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge::console
{

using
function_map
=
std::map<
	sge::font::string,
	sge::console::function
>;

}

#endif
