//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_STRING_RESULT_FWD_HPP_INCLUDED
#define SGE_PARSE_INI_STRING_RESULT_FWD_HPP_INCLUDED

#include <sge/parse/ini/start_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/parse/parse_string_error_fwd.hpp>

namespace sge::parse::ini
{

using string_result =
    fcppt::either::object<fcppt::parse::parse_string_error<char>, sge::parse::ini::start>;
}

#endif
