/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/sampler_alpha_arg_type.hpp>
#include <sge/opengl/state/convert/sampler_arg_type.hpp>
#include <sge/opengl/state/convert/sampler_color_arg_type.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>
#include <sge/renderer/state/ffp/sampler/color_op_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Arg
>
GLenum
sge::opengl::state::convert::sampler_arg_type<
	sge::renderer::state::ffp::sampler::alpha_op,
	Arg
>::get()
{
	return
		sge::opengl::state::convert::sampler_alpha_arg_type<
			Arg
		>::get();
}

template<
	typename Arg
>
GLenum
sge::opengl::state::convert::sampler_arg_type<
	sge::renderer::state::ffp::sampler::color_op,
	Arg
>::get()
{
	return
		sge::opengl::state::convert::sampler_color_arg_type<
			Arg
		>::get();
}

#define SGE_OPENGL_STATE_CONVERT_INSTANTIATE_SAMPLER_ALPHA_ARG_TYPE(\
	seq,\
	_,\
	arg_type\
) \
template \
struct \
sge::opengl::state::convert::sampler_arg_type<\
	sge::renderer::state::ffp::sampler::alpha_op,\
	sge::renderer::state::ffp::sampler:: arg_type \
>;

#define SGE_OPENGL_STATE_CONVERT_INSTANTIATE_SAMPLER_COLOR_ARG_TYPE(\
	seq,\
	_,\
	arg_type\
) \
extern \
template \
struct \
sge::opengl::state::convert::sampler_arg_type<\
	sge::renderer::state::ffp::sampler::color_op, \
	sge::renderer::state::ffp::sampler:: arg_type \
>;

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_STATE_CONVERT_INSTANTIATE_SAMPLER_ALPHA_ARG_TYPE,
	_,
	SGE_RENDERER_STATE_FFP_SAMPLER_PP_ARG_TYPES
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_STATE_CONVERT_INSTANTIATE_SAMPLER_COLOR_ARG_TYPE,
	_,
	SGE_RENDERER_STATE_FFP_SAMPLER_PP_ARG_TYPES
);
