//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_IMPL_FROM_STRING_HPP_INCLUDED
#define SGE_CONSOLE_IMPL_FROM_STRING_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::console::impl
{

sge::font::string from_string(std::string const &);

sge::font::string from_string(std::wstring const &);

}

#endif
