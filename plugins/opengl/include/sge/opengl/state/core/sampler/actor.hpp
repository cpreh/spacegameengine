//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_ACTOR_HPP_INCLUDED

#include <sge/opengl/texture/binding_fwd.hpp>
#include <fcppt/function_impl.hpp>

namespace sge::opengl::state::core::sampler
{

using actor = fcppt::function<void(sge::opengl::texture::binding const &)>;

}

#endif
