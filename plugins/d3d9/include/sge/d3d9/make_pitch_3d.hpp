//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_MAKE_PITCH_3D_HPP_INCLUDED
#define SGE_D3D9_MAKE_PITCH_3D_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/image3d/dim_fwd.hpp>
#include <sge/image3d/pitch_fwd.hpp>

namespace sge
{
namespace d3d9
{

sge::image3d::pitch const
make_pitch_3d(D3DLOCKED_BOX const &, sge::image3d::dim const &, sge::image::color::format);

}
}

#endif
