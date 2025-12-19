//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_ENTRY_DECL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_ENTRY_DECL_HPP_INCLUDED

#include <sge/parse/ini/typed/entry_error_fwd.hpp>
#include <sge/parse/ini/typed/entry_fwd.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/required.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{

template<typename Type, sge::parse::ini::typed::required Required>
class entry
{
public:
  explicit entry(std::string &&);

  static constexpr bool is_optional = (Required == sge::parse::ini::typed::required::no);

  using result_type = Type;

  [[nodiscard]]
  fcppt::either::object<sge::parse::ini::typed::entry_error, result_type>
  parse(std::string const &) const;
private:
  std::string name_;
};

}

#endif
