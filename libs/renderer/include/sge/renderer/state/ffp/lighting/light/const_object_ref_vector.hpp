//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_CONST_OBJECT_REF_VECTOR_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_CONST_OBJECT_REF_VECTOR_HPP_INCLUDED

#include <sge/renderer/state/ffp/lighting/light/const_object_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::state::ffp::lighting::light
{

using const_object_ref_vector =
    std::vector<sge::renderer::state::ffp::lighting::light::const_object_ref>;

}

#endif
