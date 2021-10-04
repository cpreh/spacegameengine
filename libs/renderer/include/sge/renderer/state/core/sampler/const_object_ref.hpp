//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_CONST_OBJECT_REF_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_CONST_OBJECT_REF_HPP_INCLUDED

#include <sge/renderer/state/core/sampler/object_fwd.hpp>
#include <fcppt/reference.hpp>


namespace sge::renderer::state::core::sampler
{

using
const_object_ref
=
fcppt::reference<
	sge::renderer::state::core::sampler::object const
>;

}

#endif
