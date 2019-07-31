//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/renderer.hpp>
#include <sge/cegui/impl/scoped_render_context.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/make_ref.hpp>


sge::cegui::impl::scoped_render_context::scoped_render_context(
	sge::cegui::impl::renderer &_renderer,
	sge::renderer::context::ffp &_render_context
)
:
	renderer_(
		_renderer
	)
{
	renderer_.render_context(
		sge::cegui::impl::optional_render_context_ref(
			fcppt::make_ref(
				_render_context
			)
		)
	);
}

sge::cegui::impl::scoped_render_context::~scoped_render_context()
{
	renderer_.render_context(
		sge::cegui::impl::optional_render_context_ref()
	);
}
