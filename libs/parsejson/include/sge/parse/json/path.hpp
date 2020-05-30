//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_PATH_HPP_INCLUDED
#define SGE_PARSE_JSON_PATH_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

class path
{
public:
	using
	sequence_type
	=
	std::vector<
		sge::charconv::utf8_string
	>;

	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	path(
		sge::charconv::utf8_string &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	path(
		sequence_type &&
	);

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	path
	operator/(
		sge::charconv::utf8_string &&
	) &&;

	[[nodiscard]]
	SGE_PARSE_JSON_DETAIL_SYMBOL
	sequence_type const &
	get() const;
private:
	sequence_type sequence_;
};

}
}
}

#endif
