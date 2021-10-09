//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_SET_OR_CREATE_HPP_INCLUDED
#define SGE_PARSE_INI_SET_OR_CREATE_HPP_INCLUDED

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sge::parse::ini
{

SGE_PARSE_INI_DETAIL_SYMBOL
void set_or_create(
    fcppt::reference<sge::parse::ini::start>,
    sge::parse::ini::section_name const &,
    sge::parse::ini::entry_name const &,
    sge::parse::ini::value const &);

}

#endif
