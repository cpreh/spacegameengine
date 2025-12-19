//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_SECTION_IMPL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_SECTION_IMPL_HPP_INCLUDED

#include <sge/parse/ini/typed/section_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Entries>
sge::parse::ini::typed::section<Entries>::section(std::string &&_name, Entries &&_entries)
    : name_{std::move(_name)}, entries_{std::move(_entries)}
{
}

#endif
