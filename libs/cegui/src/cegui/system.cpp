//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/impl/detail/system_impl.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/WindowManager.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::system::system(
	fcppt::log::context &_log_context,
	sge::cegui::load_context const &_load_context,
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_system,
	sge::viewport::manager &_viewport_manager,
	sge::cegui::cursor_visibility const _cursor_visibility,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::cegui::detail::system_impl
		>(
			_log_context,
			_load_context,
			_renderer,
			_image_system,
			_viewport_manager,
			_cursor_visibility,
			_emulate_srgb
		)
	)
{
}

sge::cegui::system::~system()
{
}

void
sge::cegui::system::update(
	sge::cegui::duration const &_duration
)
{
	impl_->update(
		_duration
	);
}

void
sge::cegui::system::render(
	sge::renderer::context::ffp &_context
)
{
	impl_->render(
		_context
	);
}

CEGUI::WindowManager &
sge::cegui::system::window_manager()
{
	return
		CEGUI::WindowManager::getSingleton();
}

CEGUI::WindowManager const &
sge::cegui::system::window_manager() const
{
	return
		CEGUI::WindowManager::getSingleton();
}

CEGUI::GUIContext &
sge::cegui::system::gui_context()
{
	return
		impl_->gui_context();
}

CEGUI::GUIContext const &
sge::cegui::system::gui_context() const
{
	return
		impl_->gui_context();
}
