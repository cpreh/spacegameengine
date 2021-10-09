//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_ALGORITHM_DECLARE_COPY_HPP_INCLUDED
#define SGE_IMAGE_ALGORITHM_DECLARE_COPY_HPP_INCLUDED

#include <sge/image/algorithm/copy.hpp>
#include <sge/image/algorithm/may_overlap_fwd.hpp>
#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>

#define SGE_IMAGE_ALGORITHM_DECLARE_COPY(tag) \
  extern template SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL void sge::image::algorithm::copy( \
      sge::image::view::const_object<tag> const &, \
      sge::image::view::object<tag> const &, \
      sge::image::algorithm::may_overlap, \
      sge::image::algorithm::uninitialized)

#endif
