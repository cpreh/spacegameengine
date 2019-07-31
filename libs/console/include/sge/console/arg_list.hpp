//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_ARG_LIST_HPP_INCLUDED
#define SGE_CONSOLE_ARG_LIST_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{

typedef
std::vector<
	sge::font::string
>
arg_list;

}
}

#endif
