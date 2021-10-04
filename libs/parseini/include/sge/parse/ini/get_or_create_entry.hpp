//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_GET_OR_CREATE_ENTRY_HPP_INCLUDED
#define SGE_PARSE_INI_GET_OR_CREATE_ENTRY_HPP_INCLUDED

#include <sge/parse/ini/entry_fwd.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/section_fwd.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::parse::ini
{

SGE_PARSE_INI_DETAIL_SYMBOL
fcppt::reference<
	sge::parse::ini::entry
>
get_or_create_entry(
	fcppt::reference<
		sge::parse::ini::section
	>,
	sge::parse::ini::entry_name const &,
	sge::parse::ini::value const &
);

}

#endif
