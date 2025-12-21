//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_MISSING_ENTRY_ERROR_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_MISSING_ENTRY_ERROR_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{
FCPPT_DECLARE_STRONG_TYPEDEF(std::string, missing_entry_error);
}

#endif
