//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/renderer.hpp>
#include <sge/cegui/impl/renderer_ref.hpp>
#include <sge/cegui/impl/scoped_render_context.hpp>
#include <sge/renderer/context/ffp_ref.hpp>

sge::cegui::impl::scoped_render_context::scoped_render_context(
    sge::cegui::impl::renderer_ref const _renderer,
    sge::renderer::context::ffp_ref const _render_context)
    : renderer_(_renderer)
{
  renderer_.get().render_context(sge::cegui::impl::optional_render_context_ref(_render_context));
}

sge::cegui::impl::scoped_render_context::~scoped_render_context()
{
  renderer_.get().render_context(sge::cegui::impl::optional_render_context_ref());
}
