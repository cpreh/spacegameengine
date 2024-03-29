//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_IMPL_MEMBER_VECTOR_HPP_INCLUDED
#define SGE_PARSE_JSON_IMPL_MEMBER_VECTOR_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/value_fwd.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/tuple/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json::impl
{

using member_vector = std::vector<
    fcppt::tuple::object<sge::charconv::utf8_string, fcppt::recursive<sge::parse::json::value>>>;

}

#endif
