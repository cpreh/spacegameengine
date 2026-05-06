//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_IS_SECTION_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_IS_SECTION_HPP_INCLUDED

#include <sge/parse/ini/typed/section_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{
template <typename T>
struct is_section : std::false_type
{
};

template <typename T>
struct is_section<sge::parse::ini::typed::section<T>> : std::true_type
{
};
}

#endif
