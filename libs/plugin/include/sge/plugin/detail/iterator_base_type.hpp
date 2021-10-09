//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_DETAIL_ITERATOR_BASE_TYPE_HPP_INCLUDED
#define SGE_PLUGIN_DETAIL_ITERATOR_BASE_TYPE_HPP_INCLUDED

#include <sge/plugin/context_fwd.hpp>
#include <sge/plugin/iterator_fwd.hpp>
#include <fcppt/iterator/base_impl.hpp>
#include <fcppt/iterator/types.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>

namespace sge::plugin::detail
{

template <typename Type>
using iterator_base_type = fcppt::iterator::base<fcppt::iterator::types<
    sge::plugin::iterator<Type>,
    sge::plugin::context<Type>,
    sge::plugin::context<Type>,
    std::ptrdiff_t,
    std::input_iterator_tag>>;

}

#endif
