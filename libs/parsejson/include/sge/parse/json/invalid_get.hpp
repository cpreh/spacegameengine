//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_INVALID_GET_HPP_INCLUDED
#define SGE_PARSE_JSON_INVALID_GET_HPP_INCLUDED

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

class SGE_CORE_DETAIL_CLASS_SYMBOL invalid_get
:
	public sge::parse::json::exception
{
public:
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	invalid_get(
		fcppt::string &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	invalid_get(
		invalid_get &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	invalid_get(
		invalid_get const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	invalid_get &
	operator=(
		invalid_get &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	invalid_get &
	operator=(
		invalid_get const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	~invalid_get() noexcept
	override;
};

}
}
}

#endif
