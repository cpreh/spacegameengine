//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json
{

template <typename T>
T find_and_convert_member(
    sge::parse::json::object const &_object, sge::parse::json::path const &_input_path)
{
  // TODO(philipp): path split
  if (_input_path.get().empty())
  {
    throw sge::parse::json::exception{FCPPT_TEXT("find_and_convert_member: Path is empty!")};
  }

  sge::parse::json::path const shortened_path{sge::parse::json::path::sequence_type{
      _input_path.get().begin(), std::prev(_input_path.get().end())}};

  fcppt::reference<sge::parse::json::object const> const found_object{
      sge::parse::json::find_object_exn(fcppt::make_cref(_object), shortened_path)};

  sge::charconv::utf8_string const &path_back(_input_path.get().back());

  try
  {
    return sge::parse::json::convert_from<T>(
        fcppt::optional::to_exception(
            fcppt::container::find_opt_mapped(found_object.get().members, path_back),
            [&shortened_path, &path_back]
            {
              return sge::parse::json::exception(
                  FCPPT_TEXT("Couldn't find member \"") +
                  sge::parse::json::detail::to_fcppt_string(path_back) +
                  FCPPT_TEXT("\" in the object \"") +
                  sge::parse::json::detail::to_fcppt_string(
                      sge::parse::json::path_to_string(shortened_path)) +
                  FCPPT_TEXT("\""));
            })
            .get()
            .get());
  }
  catch (sge::parse::json::invalid_get const &_error)
  {
    throw sge::parse::json::exception(
        FCPPT_TEXT("Unable to parse member \"") +
        sge::parse::json::detail::to_fcppt_string(path_back) + FCPPT_TEXT("\" of object \"") +
        sge::parse::json::detail::to_fcppt_string(
            sge::parse::json::path_to_string(shortened_path)) +
        FCPPT_TEXT("\": ") + _error.string());
  }
}

}

#endif
