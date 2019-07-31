//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/sampler_ternary_op.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_type.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DTEXTUREOP
sge::d3d9::state::convert::sampler_ternary_op(
	sge::renderer::state::ffp::sampler::ternary_op_type const _op
)
{
	switch(
		_op
	)
	{

	case sge::renderer::state::ffp::sampler::ternary_op_type::interpolate:
		return D3DTOP_LERP;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
