//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_FILE_RESULT_FWD_HPP_INCLUDED
#define SGE_PARSE_FILE_RESULT_FWD_HPP_INCLUDED

#include <fcppt/either/object_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::parse
{

template <typename Ch, typename Result>
using file_result =
    fcppt::either::object<fcppt::optional::object<std::basic_string<Ch>>, Result>;
}

#endif
