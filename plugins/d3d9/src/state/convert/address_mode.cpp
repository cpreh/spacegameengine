//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/address_mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DTEXTUREADDRESS
sge::d3d9::state::convert::address_mode(
	sge::renderer::state::core::sampler::address::mode const _mode
)
{
	switch(
		_mode
	)
	{
	case sge::renderer::state::core::sampler::address::mode::clamp:
		return D3DTADDRESS_CLAMP;
	case sge::renderer::state::core::sampler::address::mode::mirror_repeat:
		return D3DTADDRESS_MIRROR;
	case sge::renderer::state::core::sampler::address::mode::repeat:
		return D3DTADDRESS_WRAP;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
