//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_INFO_UNIQUE_ID_HPP_INCLUDED
#define SGE_INPUT_INFO_UNIQUE_ID_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::input::info
{

FCPPT_DECLARE_STRONG_TYPEDEF(fcppt::string, unique_id);

}

#endif
