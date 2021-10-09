//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_TRAITS_PIXEL_FORMAT_TO_STRING_HPP_INCLUDED
#define SGE_IMAGE_TRAITS_PIXEL_FORMAT_TO_STRING_HPP_INCLUDED

#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/traits/pixel/format_to_string_tpl_fwd.hpp>
#include <fcppt/string.hpp>

namespace sge::image::traits::pixel
{

template <typename Tag>
inline fcppt::string format_to_string(sge::image::traits::pixel::format<Tag> const _format)
{
  return sge::image::traits::pixel::format_to_string_tpl<Tag>::execute(_format);
}

}

#endif
