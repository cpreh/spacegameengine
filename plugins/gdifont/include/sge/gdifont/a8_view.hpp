//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GDIFONT_A8_VIEW_HPP_INCLUDED
#define SGE_GDIFONT_A8_VIEW_HPP_INCLUDED

#include <sge/image/color/a8_format.hpp>
#include <sge/image/view/basic_format.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <mizuiro/nonconst_tag.hpp>

namespace sge
{
namespace gdifont
{

typedef sge::image::view::mizuiro_type<
    sge::image::view::basic_format<2, sge::image::color::a8_format>,
    mizuiro::nonconst_tag>
    a8_view;

}
}

#endif
