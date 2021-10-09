//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/image/ds/format_to_string.hpp>
#include <sge/image/ds/tag.hpp>
#include <sge/image/ds/traits/format_to_string.hpp>
#include <sge/image/traits/pixel/format_to_string_tpl_fwd.hpp>
#include <fcppt/string.hpp>

fcppt::string sge::image::traits::pixel::format_to_string_tpl<sge::image::ds::tag>::execute(
    sge::image::ds::format const _format)
{
  return sge::image::ds::format_to_string(_format);
}
