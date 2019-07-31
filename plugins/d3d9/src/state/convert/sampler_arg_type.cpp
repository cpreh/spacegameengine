//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/sampler_alpha_arg_type.hpp>
#include <sge/d3d9/state/convert/sampler_arg_type.hpp>
#include <sge/d3d9/state/convert/sampler_color_arg_type.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>
#include <sge/renderer/state/ffp/sampler/color_op_fwd.hpp>


template<
	typename Arg
>
D3DTEXTURESTAGESTATETYPE
sge::d3d9::state::convert::sampler_arg_type<
	sge::renderer::state::ffp::sampler::alpha_op,
	Arg
>::get()
{
	return
		sge::d3d9::state::convert::sampler_alpha_arg_type<
			Arg
		>::get();
}

template<
	typename Arg
>
D3DTEXTURESTAGESTATETYPE
sge::d3d9::state::convert::sampler_arg_type<
	sge::renderer::state::ffp::sampler::color_op,
	Arg
>::get()
{
	return
		sge::d3d9::state::convert::sampler_color_arg_type<
			Arg
		>::get();
}

#define SGE_D3D9_STATE_CONVERT_INSTANTIATE_SAMPLER_ARG_TYPE(\
	op_type,\
	arg_type\
)\
template \
struct \
sge::d3d9::state::convert::sampler_arg_type<\
	op_type,\
	arg_type\
>

#define SGE_D3D9_STATE_CONVERT_INSTANTIATE_SAMPLER_ALPHA_ARG_TYPE(\
	arg_type\
) \
SGE_D3D9_STATE_CONVERT_INSTANTIATE_SAMPLER_ARG_TYPE(\
	sge::renderer::state::ffp::sampler::alpha_op, \
	arg_type \
)

#define SGE_D3D9_STATE_CONVERT_INSTANTIATE_SAMPLER_COLOR_ARG_TYPE(\
	arg_type\
) \
SGE_D3D9_STATE_CONVERT_INSTANTIATE_SAMPLER_ARG_TYPE(\
	sge::renderer::state::ffp::sampler::color_op, \
	arg_type \
)

#define SGE_D3D9_STATE_CONVERT_INSTANTIATE_ARGS(\
	macro\
)\
macro(\
	sge::renderer::state::ffp::sampler::arg1\
);\
macro(\
	sge::renderer::state::ffp::sampler::arg2\
);\
macro(\
	sge::renderer::state::ffp::sampler::arg3\
)

SGE_D3D9_STATE_CONVERT_INSTANTIATE_ARGS(
	SGE_D3D9_STATE_CONVERT_INSTANTIATE_SAMPLER_ALPHA_ARG_TYPE
);

SGE_D3D9_STATE_CONVERT_INSTANTIATE_ARGS(
	SGE_D3D9_STATE_CONVERT_INSTANTIATE_SAMPLER_COLOR_ARG_TYPE
);
