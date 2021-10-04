//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RESOURCE_TREE_DETAIL_STRIP_FILE_EXTENSION_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_STRIP_FILE_EXTENSION_HPP_INCLUDED

#include <sge/resource_tree/path_fwd.hpp>
#include <sge/resource_tree/detail/symbol.hpp>


namespace sge::resource_tree::detail
{

/**
\brief Modify a path, stripping the file extension at the end
*/
SGE_RESOURCE_TREE_DETAIL_SYMBOL
sge::resource_tree::path
strip_file_extension(
	sge::resource_tree::path const &);

}

#endif
