//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_GET_OR_CREATE_SECTION_HPP_INCLUDED
#define SGE_PARSE_INI_GET_OR_CREATE_SECTION_HPP_INCLUDED

#include <sge/parse/ini/section_fwd.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/detail/symbol.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

SGE_PARSE_INI_DETAIL_SYMBOL
sge::parse::ini::section &
get_or_create_section(
	sge::parse::ini::start &,
	sge::parse::ini::section_name const &
);

}
}
}

#endif
