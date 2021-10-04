//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_CONST_OBJECT_REF_MAP_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_CONST_OBJECT_REF_MAP_HPP_INCLUDED

#include <sge/renderer/state/core/sampler/const_object_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::state::core::sampler
{

using
const_object_ref_map
=
std::map<
	sge::renderer::texture::stage,
	sge::renderer::state::core::sampler::const_object_ref
>;

}

#endif
