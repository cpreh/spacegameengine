#include <sge/cegui/scoped_system.hpp>
#include <sge/cegui/renderer.hpp>
#include <sge/cegui/image_codec.hpp>
#include <sge/cegui/resource_provider.hpp>
#include <CEGUI/CEGUISystem.h>

sge::cegui::scoped_system::scoped_system(
	renderer &_renderer,
	image_codec &_image_codec,
	resource_provider &_resource_provider)
{
	CEGUI::System::create(
		_renderer,
		// Resource provider
		&_resource_provider,
		// XML parser
		0,
		&_image_codec,
		// Script module,
		0,
		// config file
		"",
		// log file
		"CEGUI.log");
}

sge::cegui::scoped_system::~scoped_system()
{
	CEGUI::System::destroy();
}
