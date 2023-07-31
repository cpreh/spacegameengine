//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/char_type.hpp>
#include <sge/cg/string.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::cg::program::compile_options::compile_options() : value_() {}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

sge::cg::program::compile_options::compile_options(sge::cg::char_type const **_pointers) : value_()
{
  // TODO(philipp): Refactor this
  for (; *_pointers != nullptr;
       ++_pointers // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  )
  {
    // NOLINTNEXTLINE(hicpp-use-emplace,modernize-use-emplace)
    value_.push_back(sge::cg::string{*_pointers});
  }
}

FCPPT_PP_POP_WARNING

sge::cg::program::compile_options::compile_options(string_sequence _value)
    : value_(std::move(_value))
{
}

sge::cg::program::compile_options::pointer_sequence
sge::cg::program::compile_options::pointers() const
{
  sge::cg::program::compile_options::pointer_sequence result{
      fcppt::algorithm::map<sge::cg::program::compile_options::pointer_sequence>(
          value_, [](sge::cg::string const &_string) { return _string.c_str(); })};

  result.push_back(nullptr);

  return result;
}

sge::cg::program::compile_options::string_sequence const &
sge::cg::program::compile_options::value() const
{
  return value_;
}
