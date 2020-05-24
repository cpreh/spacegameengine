//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/sampler/object_fwd.hpp>
#include <sge/renderer/state/core/sampler/scoped_single.hpp>
#include <sge/renderer/state/core/sampler/single.hpp>
#include <sge/renderer/texture/stage.hpp>


sge::renderer::state::core::sampler::scoped_single::scoped_single(
	sge::renderer::context::core_ref const _context,
	sge::renderer::texture::stage const _stage,
	sge::renderer::state::core::sampler::const_object_ref const _object
)
:
	context_(
		_context
	),
	stage_(
		_stage
	)
{
	sge::renderer::state::core::sampler::single(
		context_,
		stage_,
		sge::renderer::state::core::sampler::const_optional_object_ref(
			_object
		)
	);
}

sge::renderer::state::core::sampler::scoped_single::~scoped_single()
{
	sge::renderer::state::core::sampler::single(
		context_,
		stage_,
		sge::renderer::state::core::sampler::const_optional_object_ref()
	);
}
