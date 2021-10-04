//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_SAMPLER_SET_ONE_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SAMPLER_SET_ONE_HPP_INCLUDED

#include <sge/opengl/state/ffp/sampler/actor.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>


namespace sge::opengl::state::ffp::sampler
{

sge::opengl::state::ffp::sampler::actor
set_one(
	sge::opengl::texture::funcs::env_arg,
	sge::opengl::texture::funcs::env_int_value
);

}

#endif
