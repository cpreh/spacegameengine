/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/scoped_render_context.hpp>
#include <sge/src/cegui/texture_parameters.hpp>
#include <sge/src/cegui/to_cegui_rect.hpp>
#include <sge/src/cegui/detail/system_impl.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Font.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/Rect.h>
#include <CEGUI/Scheme.h>
#include <CEGUI/System.h>
#include <CEGUI/falagard/WidgetLookManager.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("system")
)

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::cegui::detail::system_impl::system_impl(
	sge::cegui::load_context const &_load_context,
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_system,
	sge::charconv::system &_charconv_system,
	sge::viewport::manager &_viewport_manager,
	sge::cegui::cursor_visibility::type const _cursor_visibility
)
:
	charconv_system_(
		_charconv_system
	),
	prefix_(
		_load_context.scheme_file().parent_path()
	),
	cegui_logger_(
		charconv_system_
	),
	renderer_(
		sge::cegui::texture_parameters(
			prefix_,
			_charconv_system,
			_image_system,
			_renderer
		)
	),
	image_codec_(
		_image_system
	),
	resource_provider_(
		_charconv_system
	),
	scoped_system_(
		renderer_,
		image_codec_,
		resource_provider_
	),
	gui_context_(
		renderer_.getDefaultRenderTarget()
	),
	viewport_change_connection_(
		_viewport_manager.manage_callback(
			std::tr1::bind(
				&sge::cegui::detail::system_impl::viewport_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	old_viewport_(
		sge::renderer::pixel_rect::null()
	)
{
	CEGUI::WidgetLookManager::setDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.looknfeel_directory()
				?
					*_load_context.looknfeel_directory()
				:
					prefix_.get()
			),
			_charconv_system
		)
	);

	CEGUI::Font::setDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.font_directory()
				?
					*_load_context.font_directory()
				:
					prefix_.get()
			),
			_charconv_system
		)
	);

	CEGUI::ImageManager::setImagesetDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.imageset_directory()
				?
					*_load_context.imageset_directory()
				:
					prefix_.get()
			),
			_charconv_system
		)
	);

	CEGUI::Scheme::setDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				prefix_.get()
			),
			_charconv_system
		)
	);

	CEGUI::SchemeManager::getSingleton().createFromFile(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.scheme_file().filename()
			),
			_charconv_system
		)
	);

	if(
		_cursor_visibility
		==
		sge::cegui::cursor_visibility::invisible
	)
		gui_context_.getMouseCursor().hide();

	if(
		_load_context.default_font()
	)
		gui_context_.setDefaultFont(
			&CEGUI::FontManager::getSingleton().createFreeTypeFont(
				"",
				_load_context.default_font()->font_size(),
				true,
				cegui::to_cegui_string(
					fcppt::filesystem::path_to_string(
						_load_context.default_font()->path()
					),
					_charconv_system
				)
			)
		);

	this->viewport_change(
		_viewport_manager.viewport()
	);
}
FCPPT_PP_POP_WARNING

sge::cegui::detail::system_impl::~system_impl()
{
}

void
sge::cegui::detail::system_impl::update(
	sge::cegui::duration const &_duration
)
{
	CEGUI::System::getSingleton().injectTimePulse(
		_duration.count()
	);
}

void
sge::cegui::detail::system_impl::render(
	sge::renderer::context::ffp &_context
)
{
	sge::cegui::scoped_render_context const context(
		renderer_,
		_context
	);

	gui_context_.draw();
}

CEGUI::GUIContext &
sge::cegui::detail::system_impl::gui_context()
{
	return
		gui_context_;
}

sge::charconv::system &
sge::cegui::detail::system_impl::charconv_system() const
{
	return
		charconv_system_;
}

void
sge::cegui::detail::system_impl::viewport_change(
	sge::renderer::target::viewport const &_viewport
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("viewport_change() with ")
			<< _viewport.get()
	);

	// Calling notifyDisplaySizeChanged with a null rect causes a strange problem
	if(
		sge::renderer::target::viewport_is_null(
			_viewport
		)
		||
		old_viewport_ == _viewport
	)
		return;

	CEGUI::Rectf const new_area_cegui(
		sge::cegui::to_cegui_rect<
			CEGUI::Rectf::value_type
		>(
			_viewport.get()
		)
	);

	CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		new_area_cegui.getSize()
	);

	// TODO:
	// We have to reset this manually. The cursor does receive its own
	// "notifyDisplaySizeChanged" but that (deliberately?) doesn't
	// update the constraint area
	gui_context_.getMouseCursor().setConstraintArea(
		&new_area_cegui
	);

	old_viewport_ = _viewport;
}
