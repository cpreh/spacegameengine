//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_OPTIONAL_OBJECT_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_OPTIONAL_OBJECT_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::renderer::state::ffp::sampler
{

using optional_object_unique_ptr =
    fcppt::optional::object<sge::renderer::state::ffp::sampler::object_unique_ptr>;

}

#endif
