//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_SET_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_SET_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge::opengl::state::core::sampler
{

void
set(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &
);

}

#endif
