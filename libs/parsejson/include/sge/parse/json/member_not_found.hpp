//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_MEMBER_NOT_FOUND_HPP_INCLUDED
#define SGE_PARSE_JSON_MEMBER_NOT_FOUND_HPP_INCLUDED

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

class SGE_CORE_DETAIL_CLASS_SYMBOL member_not_found
:
	public sge::parse::json::exception
{
public:
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	member_not_found(
		fcppt::string &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found(
		member_not_found &&
	)
	noexcept;

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found(
		member_not_found const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found &
	operator=(
		member_not_found &&
	)
	noexcept;

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found &
	operator=(
		member_not_found const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	~member_not_found() noexcept
	override;
};

}
}
}

#endif
