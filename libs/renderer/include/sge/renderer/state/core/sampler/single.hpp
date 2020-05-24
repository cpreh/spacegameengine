//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_SINGLE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_SINGLE_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace sampler
{

SGE_RENDERER_DETAIL_SYMBOL
void
single(
	sge::renderer::context::core_ref,
	sge::renderer::texture::stage,
	sge::renderer::state::core::sampler::const_optional_object_ref const &
);

}
}
}
}
}

#endif
