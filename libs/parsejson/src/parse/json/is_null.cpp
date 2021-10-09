//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/is_null.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>

bool sge::parse::json::is_null(sge::parse::json::value const &_value)
{
  return fcppt::variant::holds_type<sge::parse::json::null>(_value.get());
}
