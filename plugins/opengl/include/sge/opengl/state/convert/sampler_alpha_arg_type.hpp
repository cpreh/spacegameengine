//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CONVERT_SAMPLER_ALPHA_ARG_TYPE_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_SAMPLER_ALPHA_ARG_TYPE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>


namespace sge::opengl::state::convert
{

template<
	typename Arg
>
struct sampler_alpha_arg_type;

template<>
struct sampler_alpha_arg_type<
	sge::renderer::state::ffp::sampler::arg1
>
{
	static
	GLenum
	get();
};

template<>
struct sampler_alpha_arg_type<
	sge::renderer::state::ffp::sampler::arg2
>
{
	static
	GLenum
	get();
};

template<>
struct sampler_alpha_arg_type<
	sge::renderer::state::ffp::sampler::arg3
>
{
	static
	GLenum
	get();
};

}

#endif
