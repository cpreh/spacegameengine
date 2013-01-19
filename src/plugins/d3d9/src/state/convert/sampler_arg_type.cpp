/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
