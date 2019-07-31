//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/sampler_color_arg_type.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>


D3DTEXTURESTAGESTATETYPE
sge::d3d9::state::convert::sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg1
>::get()
{
	return D3DTSS_COLORARG1;
}

D3DTEXTURESTAGESTATETYPE
sge::d3d9::state::convert::sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg2
>::get()
{
	return D3DTSS_COLORARG2;
}

D3DTEXTURESTAGESTATETYPE
sge::d3d9::state::convert::sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg3
>::get()
{
	return D3DTSS_COLORARG0;
}
