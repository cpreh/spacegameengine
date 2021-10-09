//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_FUNCTION_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_FUNCTION_HPP_INCLUDED

#include <sge/image/color/impl/dynamic/algorithm/cac/source.hpp>
#include <mizuiro/color/object.hpp>

namespace sge::image::color::impl::dynamic::algorithm::cac
{

template <typename SourceFormat, typename DestFormat>
using function = mizuiro::color::object<typename DestFormat::color_format> (*)(
    sge::image::color::impl::dynamic::algorithm::cac::source<SourceFormat> const &,
    typename mizuiro::color::object<typename DestFormat::color_format>::format_store_type const &);

}

#endif
