//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_SAMPLER_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SAMPLER_ACTOR_HPP_INCLUDED

#include <sge/opengl/texture/active_level_fwd.hpp>
#include <fcppt/function_impl.hpp>

namespace sge::opengl::state::ffp::sampler
{

using actor = fcppt::function<void(sge::opengl::texture::active_level const &)>;

}

#endif
