//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGEDS2D_VIEW_CONST_OBJECT_HPP_INCLUDED
#define SGE_IMAGEDS2D_VIEW_CONST_OBJECT_HPP_INCLUDED

#include <sge/image/ds/traits/static_formats.hpp> // IWYU pragma: keep
#include <sge/image/view/const_object.hpp> // IWYU pragma: keep
#include <sge/image/view/declare_const_object.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/traits/color_tag.hpp> // IWYU pragma: keep
#include <sge/imageds2d/traits/dimension.hpp> // IWYU pragma: keep
#include <sge/imageds2d/view/const_object_fwd.hpp> // IWYU pragma: export

SGE_IMAGE_VIEW_DECLARE_CONST_OBJECT(sge::imageds2d::tag);

#endif
