//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_IS_ENTRY_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_IS_ENTRY_HPP_INCLUDED

#include <sge/parse/ini/typed/entry_fwd.hpp>
#include <sge/parse/ini/typed/required_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{
template <typename T>
struct is_entry : std::false_type
{
};

template <typename T, sge::parse::ini::typed::required R>
struct is_entry<sge::parse::ini::typed::entry<T, R>> : std::true_type
{
};
}

#endif
