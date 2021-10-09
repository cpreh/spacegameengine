//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/event/base.hpp>
#include <sge/renderer/event/render.hpp>
#include <awl/window/reference.hpp>

sge::renderer::event::render::render(awl::window::reference const _window)
    : sge::renderer::event::base{_window}
{
}

sge::renderer::event::render::~render() = default;
