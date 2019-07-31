//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RESOURCE_TREE_DETAIL_STRIP_PATH_PREFIX_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_STRIP_PATH_PREFIX_HPP_INCLUDED

#include <sge/resource_tree/path_fwd.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <sge/resource_tree/detail/symbol.hpp>


namespace sge
{
namespace resource_tree
{
namespace detail
{

SGE_RESOURCE_TREE_DETAIL_SYMBOL
sge::resource_tree::path
strip_path_prefix(
	sge::resource_tree::detail::base_path const &,
	sge::resource_tree::detail::sub_path const &
);

}
}
}

#endif
