//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_ENTRY_IMPL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_ENTRY_IMPL_HPP_INCLUDED

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/typed/entry_decl.hpp>
#include <sge/parse/ini/typed/entry_error.hpp>
#include <sge/parse/ini/typed/required.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <typeinfo> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

template <typename Type, sge::parse::ini::typed::required Required>
sge::parse::ini::typed::entry<Type, Required>::entry(std::string &&_name) : name_{std::move(_name)}
{
}

template <typename Type, sge::parse::ini::typed::required Required>
fcppt::either::object<
    sge::parse::ini::typed::entry_error,
    typename sge::parse::ini::typed::entry<Type, Required>::result_type>
sge::parse::ini::typed::entry<Type, Required>::parse(std::string const &_value) const
{
  return fcppt::either::from_optional(
      fcppt::extract_from_string<result_type>(_value),
      [this, &_value]
      {
        return sge::parse::ini::typed::entry_error{
            typeid(result_type),
            sge::parse::ini::entry_name{this->name_},
            sge::parse::ini::value{_value}};
      });
}

#endif
