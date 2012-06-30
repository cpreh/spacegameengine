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
#include <sge/cegui/structure_cast.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/src/cegui/scoped_render_context.hpp>
#include <sge/src/cegui/texture_parameters.hpp>
#include <sge/src/cegui/detail/system_impl.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
// TODO: what is needed here?
#include <falagard/CEGUIFalWidgetLookManager.h>
#include <elements/CEGUIEditbox.h>
#include <elements/CEGUIFrameWindow.h>
#include <boost/filesystem/path.hpp>
#include <CEGUIAnimationManager.h>
#include <CEGUIDefaultResourceProvider.h>
#include <CEGUIFont.h>
#include <CEGUIFontManager.h>
#include <CEGUIImageset.h>
#include <CEGUIScheme.h>
#include <CEGUIScriptModule.h>
#include <CEGUISystem.h>
#include <CEGUIWindow.h>
#include <CEGUIWindowManager.h>
#include <CEGUIXMLParser.h>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::cegui::detail::system_impl::system_impl(
	sge::cegui::load_context const &_load_context,
	sge::renderer::device &_renderer,
	sge::image2d::system &_image_system,
	sge::charconv::system &_charconv_system,
	sge::viewport::manager &_viewport,
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
	viewport_change_connection_(
		_viewport.manage_callback(
			std::tr1::bind(
				&sge::cegui::detail::system_impl::viewport_change,
				this
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

	CEGUI::Imageset::setDefaultResourceGroup(
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

	CEGUI::SchemeManager::getSingleton().create(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.scheme_file().filename()
			),
			_charconv_system
		)
	);

	// TODO: make a new function for this
	switch(
		_cursor_visibility
	)
	{
		case cursor_visibility::visible:
			CEGUI::System::getSingleton().setDefaultMouseCursor(
				CEGUI::ImagesetManager::getSingleton().getIterator().getCurrentValue()->getName(),
				"MouseArrow"
			);
		break;
		case cursor_visibility::invisible:
			CEGUI::MouseCursor::getSingleton().hide();
		break;
	}

	if(
		_load_context.default_font()
	)
		CEGUI::System::getSingleton().setDefaultFont(
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

	this->viewport_change();
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
	sge::renderer::context::object &_context
)
{
	sge::cegui::scoped_render_context const context(
		renderer_,
		_context
	);

	CEGUI::System::getSingleton().renderGUI();
}

void
sge::cegui::detail::system_impl::viewport_change()
{
	sge::renderer::pixel_rect const new_area_fcppt(
		renderer_.impl().onscreen_target().viewport().get()
	);

	// Calling notifyDisplaySizeChanged with a null rect causes a strange problem
	if(
		!new_area_fcppt.content()
		||
		old_viewport_ == new_area_fcppt
	)
		return;

	CEGUI::Rect const new_area_cegui(
		sge::cegui::structure_cast(
			new_area_fcppt
		)
	);

	CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		new_area_cegui.getSize()
	);

	// We have to reset this manually. The cursor does receive its own
	// "notifyDisplaySizeChanged" but that (deliberately?) doesn't
	// update the constraint area
	CEGUI::MouseCursor::getSingleton().setConstraintArea(
		&new_area_cegui
	);

	old_viewport_ = new_area_fcppt;
}
