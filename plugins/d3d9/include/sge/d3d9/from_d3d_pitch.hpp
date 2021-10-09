//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_FROM_D3D_PITCH_HPP_INCLUDED
#define SGE_D3D9_FROM_D3D_PITCH_HPP_INCLUDED

#include <sge/image/basic_dim.hpp>
#include <sge/image/basic_pitch.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/dim/at.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/init.hpp>
#include <fcppt/math/dim/narrow_cast.hpp>

namespace sge
{
namespace d3d9
{

template <sge::image::size_type Dim>
sge::image::basic_pitch<Dim> from_d3d_pitch(
    sge::image::basic_pitch<Dim> const &_pitches,
    sge::image::basic_dim<Dim> const &_dim,
    sge::image::color::format const _format)
{
  return fcppt::math::dim::init<sge::image::basic_pitch<Dim>>(
      [&_pitches, &_dim, _format](auto const _index)
      {
        return fcppt::math::dim::at<_index>(_pitches) -
               fcppt::cast::to_signed(
                   fcppt::math::dim::contents(
                       fcppt::math::dim::narrow_cast<sge::image::basic_dim<Dim - 1u>>(_dim)) *
                   sge::image::color::format_stride(_format));
      });
}

}
}

#endif
