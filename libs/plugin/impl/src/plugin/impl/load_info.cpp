//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/plugin/info.hpp>
#include <sge/plugin/impl/load_info.hpp>
#include <sge/plugin/impl/library/load_function.hpp>
#include <sge/plugin/impl/library/object.hpp>
#include <sge/plugin/impl/library/version_function_name.hpp>
#include <sge/plugin/library/detail/version_function.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::plugin::info sge::plugin::impl::load_info(std::filesystem::path const &_path)
{
  sge::plugin::library::object lib{std::filesystem::path{_path}};

  return sge::plugin::impl::library::load_function<sge::plugin::library::detail::version_function>(
      fcppt::make_ref(lib), sge::plugin::impl::library::version_function_name())();
}
