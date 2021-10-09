//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_BASIC_VARIANT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_BASIC_VARIANT_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/color/impl/dynamic/view/basic_elements.hpp>
#include <fcppt/variant/from_list_fwd.hpp>

namespace sge::image::color::impl::dynamic::view
{

template <sge::image::size_type Dim, typename Constness>
using basic_variant = fcppt::variant::from_list<
    sge::image::color::impl::dynamic::view::basic_elements<Dim, Constness>>;

}

#endif
