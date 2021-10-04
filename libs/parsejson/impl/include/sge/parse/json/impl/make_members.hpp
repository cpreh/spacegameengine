//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_IMPL_MAKE_MEMBERS_HPP_INCLUDED
#define SGE_PARSE_JSON_IMPL_MAKE_MEMBERS_HPP_INCLUDED

#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/impl/member_vector.hpp>
#include <fcppt/parse/result.hpp>


namespace sge::parse::json::impl
{

fcppt::parse::result<
	char,
	sge::parse::json::member_map
>
make_members(
	sge::parse::json::impl::member_vector &&
);

}

#endif
