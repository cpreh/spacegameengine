//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_START_HPP_INCLUDED
#define SGE_PARSE_INI_START_HPP_INCLUDED

#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/detail/symbol.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

struct start
{
	SGE_PARSE_INI_DETAIL_SYMBOL
	explicit
	start(
		sge::parse::ini::section_vector &&
	);

	sge::parse::ini::section_vector sections; // NOLINT(misc-non-private-member-variables-in-classes)
};

SGE_PARSE_INI_DETAIL_SYMBOL
bool
operator==(
	sge::parse::ini::start const &,
	sge::parse::ini::start const &
);

}
}
}

#endif
