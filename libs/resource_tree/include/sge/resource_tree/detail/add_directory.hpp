//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RESOURCE_TREE_DETAIL_ADD_DIRECTORY_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ADD_DIRECTORY_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/path_to_resource_function.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/element_impl.hpp>
#include <sge/resource_tree/detail/path_with_resource_impl.hpp>
#include <sge/resource_tree/detail/strip_file_extension.hpp>
#include <sge/resource_tree/detail/strip_path_prefix.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <fcppt/error_code_to_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/filesystem/make_directory_range.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <system_error>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::resource_tree::detail
{

template <typename T, typename Rng>
sge::resource_tree::detail::element<T, Rng> add_directory(
    sge::resource_tree::detail::base_path const &_base_path,
    sge::resource_tree::detail::sub_path const &_sub_path,
    sge::resource_tree::path_to_resource_function<T> const &_path_to_resource,
    fcppt::reference<Rng> const _random_generator)
{
  using element_type = sge::resource_tree::detail::element<T, Rng>;

  using resource_container = typename element_type::resource_container;

  auto resources(fcppt::algorithm::map_optional<resource_container>(
      fcppt::either::to_exception(
          fcppt::filesystem::make_directory_range(
              _sub_path.get(), std::filesystem::directory_options::none),
          [](std::error_code const _error)
          { return sge::resource_tree::exception{fcppt::error_code_to_string(_error)}; }),
      [&_sub_path, &_path_to_resource](std::filesystem::path const &_path)
      {
        using path_type = sge::resource_tree::detail::path_with_resource<T>;

        using result_type = fcppt::optional::object<path_type>;

        return std::filesystem::is_regular_file(_path)
                   ? result_type{path_type{
                         sge::resource_tree::detail::strip_file_extension(
                             sge::resource_tree::detail::strip_path_prefix(
                                 sge::resource_tree::detail::base_path(_sub_path.get()),
                                 sge::resource_tree::detail::sub_path(_path))),
                         _path_to_resource(_path)}}
                   : result_type{};
      }));

  return
      // Second, create the element structure containing the files
      element_type{
          sge::resource_tree::detail::strip_path_prefix(_base_path, _sub_path),
          std::move(resources),
          _random_generator};
}

}

#endif
