/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/system.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/time/funit.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/viewport.hpp>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIDefaultResourceProvider.h>
#include <CEGUI/falagard/CEGUIFalWidgetLookManager.h>
#include <CEGUI/CEGUIImageset.h>
#include <CEGUI/CEGUIFont.h>
#include <CEGUI/CEGUIFontManager.h>
#include <CEGUI/CEGUIScheme.h>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIScriptModule.h>
#include <CEGUI/CEGUIXMLParser.h>
#include <CEGUI/CEGUIWindow.h>
#include <CEGUI/elements/CEGUIFrameWindow.h>
#include <CEGUI/elements/CEGUIEditbox.h>
#include <CEGUI/CEGUIAnimationManager.h>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/duration.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/filesystem/remove_filename.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
// YES, OF COURSE I HAVE TO INCLUDE THAT!
#include <fcppt/function/object.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <set>

sge::cegui::system::system(
	load_context const &_load_context,
	sge::renderer::device &_renderer,
	sge::image2d::multi_loader &_image_loader,
	sge::charconv::system &_charconv_system,
	sge::viewport::manager &_viewport,
	cursor_visibility::type const _cursor_visibility)
:
	charconv_system_(
		_charconv_system),
	prefix_(
		fcppt::filesystem::remove_filename(
			_load_context.scheme_file())),
	cegui_logger_(),
	renderer_(
		*this,
		_renderer),
	image_codec_(
		_image_loader),
	resource_provider_(
		_charconv_system),
	system_(
		renderer_,
		image_codec_,
		resource_provider_),
	viewport_change_connection_(
		_viewport.manage_callback(
			boost::bind(
				&system::viewport_change,
				this))),
	old_viewport_(
		sge::renderer::pixel_rect::null())
{
	CEGUI::WidgetLookManager::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.looknfeel_directory()
				?
					*_load_context.looknfeel_directory()
				:
					prefix_),
			_charconv_system));

	CEGUI::Font::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.font_directory()
				?
					*_load_context.font_directory()
				:
					prefix_),
			_charconv_system));

	CEGUI::Imageset::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.imageset_directory()
				?
					*_load_context.imageset_directory()
				:
					prefix_),
			_charconv_system));

	CEGUI::Scheme::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				prefix_),
			_charconv_system));

	CEGUI::SchemeManager::getSingleton().create(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.scheme_file().filename()),
			_charconv_system));

	switch(_cursor_visibility)
	{
		case cursor_visibility::visible:
			CEGUI::System::getSingleton().setDefaultMouseCursor(
				CEGUI::ImagesetManager::getSingleton().getIterator().getCurrentValue()->getName(),
				"MouseArrow");
		break;
		case cursor_visibility::invisible:
			CEGUI::MouseCursor::getSingleton().hide();
		break;
	}
	
	if(_load_context.default_font())
		CEGUI::System::getSingleton().setDefaultFont(	
			&CEGUI::FontManager::getSingleton().createFreeTypeFont(
				"",
				_load_context.default_font()->font_size(),
				true,
				cegui::to_cegui_string(
					fcppt::filesystem::path_to_string(
						_load_context.default_font()->path()),
					_charconv_system)));

	viewport_change();
}

void
sge::cegui::system::update(
	sge::time::duration const &d)
{
	CEGUI::System::getSingleton().injectTimePulse(
		static_cast<unit>(
			fcppt::chrono::duration_cast<fcppt::chrono::milliseconds>(
				d).count())/static_cast<unit>(1000));
}

void
sge::cegui::system::render()
{
	CEGUI::System::getSingleton().renderGUI();
}

sge::cegui::system::~system()
{
}

void
sge::cegui::system::viewport_change()
{
	sge::renderer::pixel_rect new_area_fcppt = 
		renderer_.impl().onscreen_target().viewport().get();
	// Calling notifyDisplaySizeChanged with a null rect causes a strange problem
	if(!new_area_fcppt.content() || old_viewport_ == new_area_fcppt)
		return;
	CEGUI::Rect const new_area_cegui = 
		structure_cast(
			new_area_fcppt);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		new_area_cegui.getSize());
	// We have to reset this manually. The cursor does receive its own
	// "notifyDisplaySizeChanged" but that (deliberately?) doesn't
	// update the constraint area
	CEGUI::MouseCursor::getSingleton().setConstraintArea(
		&new_area_cegui);
	old_viewport_ = new_area_fcppt;
}

sge::charconv::system &
sge::cegui::system::charconv_system() const
{
	return charconv_system_;
}

sge::image2d::multi_loader &
sge::cegui::system::image_loader() const
{
	return image_codec_.loader();
}

sge::renderer::device &
sge::cegui::system::renderer() const
{
	return renderer_.impl();
}

fcppt::filesystem::path const
sge::cegui::system::to_absolute_path(
	CEGUI::String const &filename,
	CEGUI::String const &)
{
	return prefix_ / from_cegui_string(filename,charconv_system_);
}

