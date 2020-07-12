//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LOG_OPTION_CONTAINER_HPP_INCLUDED
#define SGE_LOG_OPTION_CONTAINER_HPP_INCLUDED

#include <sge/log/option.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace log
{

using
option_container
=
std::vector<
	sge::log::option
>;

}
}

#endif
