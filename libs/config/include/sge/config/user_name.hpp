//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONFIG_USER_NAME_HPP_INCLUDED
#define SGE_CONFIG_USER_NAME_HPP_INCLUDED

#include <sge/config/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace config
{

SGE_CONFIG_DETAIL_SYMBOL
fcppt::string
user_name();

}
}

#endif
