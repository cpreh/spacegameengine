//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RESOURCE_TREE_DETAIL_ELEMENT_VECTOR_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ELEMENT_VECTOR_HPP_INCLUDED

#include <sge/resource_tree/detail/element_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::resource_tree::detail
{

template <typename T, typename Rng>
using element_vector = std::vector<sge::resource_tree::detail::element<T, Rng>>;

}

#endif
