//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/context/scoped_offscreen_target.hpp>
#include <sge/renderer/target/offscreen_ref.hpp>
#include <sge/renderer/target/optional_offscreen_ref.hpp>


sge::renderer::context::scoped_offscreen_target::scoped_offscreen_target(
	sge::renderer::context::core_ref const _context,
	sge::renderer::target::offscreen_ref const _target
)
:
	context_(
		_context
	)
{
	context_.get().offscreen_target(
		sge::renderer::target::optional_offscreen_ref(
			_target
		)
	);
}

sge::renderer::context::scoped_offscreen_target::~scoped_offscreen_target()
{
	context_.get().offscreen_target(
		sge::renderer::target::optional_offscreen_ref()
	);
}
