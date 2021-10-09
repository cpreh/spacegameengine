//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_SAMPLER_CREATE_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SAMPLER_CREATE_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>

namespace sge::opengl::state::ffp::sampler
{

sge::renderer::state::ffp::sampler::object_unique_ptr
create(sge::renderer::state::ffp::sampler::parameters const &);

}

#endif
