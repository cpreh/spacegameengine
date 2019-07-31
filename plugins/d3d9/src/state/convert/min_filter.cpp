//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/min_filter.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <fcppt/assert/unreachable.hpp>


DWORD
sge::d3d9::state::convert::min_filter(
	sge::renderer::state::core::sampler::filter::normal::min const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::core::sampler::filter::normal::min::point:
		return D3DTEXF_POINT;
	case sge::renderer::state::core::sampler::filter::normal::min::linear:
		return D3DTEXF_LINEAR;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
