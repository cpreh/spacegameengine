//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RESOURCE_TREE_DETAIL_PATH_WITH_RESOURCE_DECL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_PATH_WITH_RESOURCE_DECL_HPP_INCLUDED

#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/path_with_resource_fwd.hpp> // IWYU pragma: keep

namespace sge::resource_tree::detail
{

/**
\brief Represents a pair of a path and a resource
*/
template <typename T>
class path_with_resource
{
public:
  path_with_resource(sge::resource_tree::path &&, T);

  [[nodiscard]] sge::resource_tree::path const &path() const;

  [[nodiscard]] T const &resource() const;

private:
  sge::resource_tree::path path_;

  T resource_;
};

}

#endif
