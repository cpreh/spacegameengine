//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/plugin/impl/library/error.hpp>
#include <sge/plugin/library/symbol_not_found.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::plugin::library::symbol_not_found::symbol_not_found(
    fcppt::string &&_library_name, sge::plugin::library::symbol_string &&_symbol)
    : sge::plugin::library::exception(
          FCPPT_TEXT("Failed to load function ") + fcppt::from_std_string(_symbol) +
          FCPPT_TEXT(" from object::library ") + _library_name + FCPPT_TEXT(" : ") +
          sge::plugin::impl::library::error()),
      library_name_(std::move(_library_name)),
      symbol_(std::move(_symbol))
{
}

sge::plugin::library::symbol_not_found::symbol_not_found(symbol_not_found &&) noexcept = default;

sge::plugin::library::symbol_not_found::symbol_not_found(symbol_not_found const &) = default;

sge::plugin::library::symbol_not_found &
sge::plugin::library::symbol_not_found::operator=(symbol_not_found &&) noexcept = default;

sge::plugin::library::symbol_not_found &
sge::plugin::library::symbol_not_found::operator=(symbol_not_found const &) = default;

fcppt::string const &sge::plugin::library::symbol_not_found::library_name() const
{
  return library_name_;
}

sge::plugin::library::symbol_string const &sge::plugin::library::symbol_not_found::symbol() const
{
  return symbol_;
}

sge::plugin::library::symbol_not_found::~symbol_not_found() = default;
