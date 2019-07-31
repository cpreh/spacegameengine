//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/fog_mode.hpp>
#include <sge/renderer/state/ffp/fog/mode.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DFOGMODE
sge::d3d9::state::convert::fog_mode(
	sge::renderer::state::ffp::fog::mode const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::ffp::fog::mode::linear:
		return D3DFOG_LINEAR;
	case sge::renderer::state::ffp::fog::mode::exp:
		return D3DFOG_EXP;
	case sge::renderer::state::ffp::fog::mode::exp2:
		return D3DFOG_EXP2;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
