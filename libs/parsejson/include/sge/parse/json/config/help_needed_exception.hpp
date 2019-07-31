//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONFIG_HELP_NEEDED_EXCEPTION_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_HELP_NEEDED_EXCEPTION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace config
{

class SGE_CORE_DETAIL_CLASS_SYMBOL help_needed_exception
:
	public sge::parse::json::exception
{
public:
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	help_needed_exception(
		fcppt::string &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	help_needed_exception(
		help_needed_exception &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	help_needed_exception(
		help_needed_exception const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	help_needed_exception &
	operator=(
		help_needed_exception &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	help_needed_exception &
	operator=(
		help_needed_exception const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	~help_needed_exception() noexcept
	override;
};

}
}
}
}

#endif
