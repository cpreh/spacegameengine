//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RESOURCE_TREE_PATH_TO_RESOURCE_FUNCTION_HPP_INCLUDED
#define SGE_RESOURCE_TREE_PATH_TO_RESOURCE_FUNCTION_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::resource_tree
{

template <typename T>
using path_to_resource_function = fcppt::function<T(std::filesystem::path const &)>;

}

#endif
