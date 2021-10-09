//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_SKIPPER_HPP_INCLUDED
#define SGE_PARSE_INI_SKIPPER_HPP_INCLUDED

#include <fcppt/parse/blank_set.hpp>
#include <fcppt/parse/skipper/char_set.hpp>
#include <fcppt/parse/skipper/operators/repetition.hpp>

namespace sge::parse::ini
{

inline auto skipper() { return *fcppt::parse::skipper::char_set{fcppt::parse::blank_set<char>()}; }

}

#endif
