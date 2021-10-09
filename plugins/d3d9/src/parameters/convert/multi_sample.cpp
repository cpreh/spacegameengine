//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/convert/multi_sample.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>

D3DMULTISAMPLE_TYPE
sge::d3d9::parameters::convert::multi_sample(
    sge::renderer::pixel_format::optional_multi_samples const &_opt_samples)
{
  return fcppt::optional::maybe(
      _opt_samples,
      fcppt::const_(D3DMULTISAMPLE_NONE),
      [](sge::renderer::pixel_format::multi_samples const _samples)
      {
        switch (_samples.get())
        {
        case 0:
        case 1:
          return D3DMULTISAMPLE_NONE;
        case 2:
          return D3DMULTISAMPLE_2_SAMPLES;
        case 3:
          return D3DMULTISAMPLE_3_SAMPLES;
        case 4:
          return D3DMULTISAMPLE_4_SAMPLES;
        case 5:
          return D3DMULTISAMPLE_5_SAMPLES;
        case 6:
          return D3DMULTISAMPLE_6_SAMPLES;
        case 7:
          return D3DMULTISAMPLE_7_SAMPLES;
        case 8:
          return D3DMULTISAMPLE_8_SAMPLES;
        case 9:
          return D3DMULTISAMPLE_9_SAMPLES;
        case 10:
          return D3DMULTISAMPLE_10_SAMPLES;
        case 11:
          return D3DMULTISAMPLE_11_SAMPLES;
        case 12:
          return D3DMULTISAMPLE_12_SAMPLES;
        case 13:
          return D3DMULTISAMPLE_13_SAMPLES;
        case 14:
          return D3DMULTISAMPLE_14_SAMPLES;
        case 15:
          return D3DMULTISAMPLE_15_SAMPLES;
        case 16:
          return D3DMULTISAMPLE_16_SAMPLES;
        }

        throw sge::renderer::exception{
            FCPPT_TEXT("Invalid multi_sample_type value (must be <= 16)!")};
      });
}
