//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_SAMPLER_SET_ONE_ARG_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SAMPLER_SET_ONE_ARG_HPP_INCLUDED

#include <sge/opengl/state/convert/sampler_arg.hpp>
#include <sge/opengl/state/convert/sampler_arg_type.hpp>
#include <sge/opengl/state/ffp/sampler/actor.hpp>
#include <sge/opengl/state/ffp/sampler/set_one.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>


namespace sge::opengl::state::ffp::sampler
{

template<
	typename OpType,
	typename Arg
>
sge::opengl::state::ffp::sampler::actor
set_one_arg(
	Arg const _arg
)
{
	return
		sge::opengl::state::ffp::sampler::set_one(
			sge::opengl::texture::funcs::env_arg{
				sge::opengl::state::convert::sampler_arg_type<
					OpType,
					Arg
				>::get()
			},
			fcppt::strong_typedef_construct_cast<
				sge::opengl::texture::funcs::env_int_value,
				fcppt::cast::static_cast_fun
			>(
				sge::opengl::state::convert::sampler_arg(
					_arg.get()
				)
			)
		);
}

}

#endif
