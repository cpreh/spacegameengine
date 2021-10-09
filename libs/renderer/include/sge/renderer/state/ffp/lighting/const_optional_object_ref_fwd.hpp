//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_CONST_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_CONST_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED

#include <sge/renderer/state/ffp/lighting/object_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>

namespace sge::renderer::state::ffp::lighting
{

using const_optional_object_ref =
    fcppt::optional::reference<sge::renderer::state::ffp::lighting::object const>;

}

#endif
