//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_NONCONST_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_NONCONST_HPP_INCLUDED

#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_NONCONST(tag, macro) \
  macro(tag, const_object); \
\
  macro(tag, object)

#endif
