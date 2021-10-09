//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONFIG_GETENV_HPP_INCLUDED
#define SGE_CONFIG_GETENV_HPP_INCLUDED

#include <sge/config/detail/symbol.hpp>
#include <fcppt/optional_string_fwd.hpp>
#include <fcppt/string.hpp>

namespace sge::config
{

SGE_CONFIG_DETAIL_SYMBOL
fcppt::optional_string getenv(fcppt::string const &);

}

#endif
