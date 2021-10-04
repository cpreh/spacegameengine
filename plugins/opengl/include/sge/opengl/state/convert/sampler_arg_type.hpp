//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CONVERT_SAMPLER_ARG_TYPE_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_SAMPLER_ARG_TYPE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/color_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/pp_arg_types.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::state::convert
{

template<
	typename OpType,
	typename Arg
>
struct sampler_arg_type;

template<
	typename Arg
>
struct sampler_arg_type<
	sge::renderer::state::ffp::sampler::alpha_op,
	Arg
>
{
	static
	GLenum
	get();
};

template<
	typename Arg
>
struct sampler_arg_type<
	sge::renderer::state::ffp::sampler::color_op,
	Arg
>
{
	static
	GLenum
	get();
};

}

#define SGE_OPENGL_STATE_CONVERT_DECLARE_SAMPLER_ALPHA_ARG_TYPE(\
	seq,\
	_,\
	arg_type\
) \
extern \
template \
struct \
sge::opengl::state::convert::sampler_arg_type<\
	sge::renderer::state::ffp::sampler::alpha_op,\
	sge::renderer::state::ffp::sampler:: arg_type \
>;

#define SGE_OPENGL_STATE_CONVERT_DECLARE_SAMPLER_COLOR_ARG_TYPE(\
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
	SGE_OPENGL_STATE_CONVERT_DECLARE_SAMPLER_ALPHA_ARG_TYPE,
	_,
	SGE_RENDERER_STATE_FFP_SAMPLER_PP_ARG_TYPES
)

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_STATE_CONVERT_DECLARE_SAMPLER_COLOR_ARG_TYPE,
	_,
	SGE_RENDERER_STATE_FFP_SAMPLER_PP_ARG_TYPES
)

#endif
