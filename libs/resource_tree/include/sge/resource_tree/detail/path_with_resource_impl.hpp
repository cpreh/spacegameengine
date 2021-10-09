//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RESOURCE_TREE_DETAIL_PATH_WITH_RESOURCE_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_PATH_WITH_RESOURCE_IMPL_HPP_INCLUDED

#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/path_with_resource_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename T>
sge::resource_tree::detail::path_with_resource<T>::path_with_resource(
    sge::resource_tree::path &&_path, T _resource)
    : path_(std::move(_path)), resource_(std::move(_resource))
{
}

template <typename T>
sge::resource_tree::path const &sge::resource_tree::detail::path_with_resource<T>::path() const
{
  return path_;
}

template <typename T>
T const &sge::resource_tree::detail::path_with_resource<T>::resource() const
{
  return resource_;
}

#endif
