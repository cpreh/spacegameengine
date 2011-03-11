#include <sge/cegui/system.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/time/funit.hpp>
#include <sge/systems/instance.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/viewport.hpp>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIDefaultResourceProvider.h>
#include <CEGUI/falagard/CEGUIFalWidgetLookManager.h>
#include <CEGUI/CEGUIImageset.h>
#include <CEGUI/CEGUIFont.h>
#include <CEGUI/CEGUIScheme.h>
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
	fcppt::filesystem::path const &scheme_file,
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader &_image_loader,
	sge::charconv::system_ptr const _charconv_system,
	sge::systems::instance &_systems,
	sge::input::keyboard::device &_keyboard,
	sge::input::mouse::device &_mouse)
:
	prefix_(
		fcppt::filesystem::remove_filename(
			scheme_file)),
	cegui_logger_(),
	renderer_(
		*this,
		_renderer),
	image_codec_(
		_image_loader),
	resource_provider_(
		prefix_,
		_charconv_system),
	system_(
		renderer_,
		image_codec_,
		resource_provider_),
	input_(
		_keyboard,
		_mouse,
		_charconv_system,
		CEGUI::System::getSingleton()),
	viewport_change_connection_(
		_systems.manage_viewport_callback(
			boost::bind(
				&system::viewport_change,
				this,
				_1))),
	old_viewport_(
		sge::renderer::pixel_rect::null())
{
	CEGUI::SchemeManager::getSingleton().create(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				scheme_file.filename()),
			_charconv_system));
#if 0
	CEGUI::SchemeManager::getSingleton().create(
		fcppt::filesystem::path_to_string(
			scheme_file.filename()).c_str()/*,
		_charconv_system)*/);
#endif

	CEGUI::System::getSingleton().setDefaultMouseCursor(
		CEGUI::ImagesetManager::getSingleton().getIterator().getCurrentValue()->getName(),
		"MouseArrow");

	viewport_change(
		sge::renderer::device_ptr());
}

void
sge::cegui::system::update(
	sge::time::duration const &d)
{
	input_.update(
		static_cast<sge::time::funit>(
			fcppt::chrono::duration_cast<fcppt::chrono::milliseconds>(
			d).count())
			/static_cast<sge::time::funit>(1000));
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
sge::cegui::system::viewport_change(
	sge::renderer::device_ptr)
{
	sge::renderer::pixel_rect new_area_fcppt = 
		renderer_.impl()->onscreen_target()->viewport().get();
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

sge::image2d::multi_loader &
sge::cegui::system::image_loader() const
{
	return image_codec_.loader();
}

sge::renderer::device_ptr const
sge::cegui::system::renderer() const
{
	return renderer_.impl();
}

fcppt::filesystem::path const
sge::cegui::system::to_absolute_path(
	CEGUI::String const &filename,
	CEGUI::String const &resource_group)
{
	return 
		resource_provider_.to_absolute_path(
			filename,
			resource_group);
}

