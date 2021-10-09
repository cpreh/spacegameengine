//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/d3d9/cg/scoped_device_fwd.hpp>
#include <sge/d3d9/cg/profile/vertex.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <Cg/cgD3D9.h>
#include <fcppt/config/external_end.hpp>

sge::cg::profile::object const sge::d3d9::cg::profile::vertex(sge::d3d9::cg::scoped_device const &)
{
  CGprofile const ret(::cgD3D9GetLatestVertexProfile());

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgD3D9GetLatestVertexProfile failed"), sge::renderer::exception)

  FCPPT_ASSERT_ERROR(ret != CG_PROFILE_UNKNOWN);

  return sge::cg::profile::object(ret);
}
