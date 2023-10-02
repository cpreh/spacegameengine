//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE3D_STORE_OBJECT_HPP_INCLUDED
#define SGE_IMAGE3D_STORE_OBJECT_HPP_INCLUDED

#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/color/traits/static_formats.hpp>
#include <sge/image/store/declare_object.hpp>
#include <sge/image3d/store/a8.hpp>
#include <sge/image3d/store/bgr32f.hpp>
#include <sge/image3d/store/bgr8.hpp>
#include <sge/image3d/store/bgra32f.hpp>
#include <sge/image3d/store/bgra8.hpp>
#include <sge/image3d/store/bgrx8.hpp>
#include <sge/image3d/store/l8.hpp>
#include <sge/image3d/store/la8.hpp>
#include <sge/image3d/store/object_fwd.hpp> // IWYU pragma: export
#include <sge/image3d/store/r32f.hpp>
#include <sge/image3d/store/rgb32f.hpp>
#include <sge/image3d/store/rgb8.hpp>
#include <sge/image3d/store/rgba32f.hpp>
#include <sge/image3d/store/rgba8.hpp>
#include <sge/image3d/store/rgbx8.hpp>
#include <sge/image3d/store/sbgr8.hpp>
#include <sge/image3d/store/sbgra8.hpp>
#include <sge/image3d/store/srgb8.hpp>
#include <sge/image3d/store/srgba8.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/traits/dimension.hpp>

SGE_IMAGE_STORE_DECLARE_OBJECT(sge::image3d::tag);

#endif
