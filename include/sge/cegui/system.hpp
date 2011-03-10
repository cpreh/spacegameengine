#ifndef SGE_CEGUI_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_SYSTEM_HPP_INCLUDED

#include <CEGUI/CEGUIString.h>
#include <sge/cegui/renderer.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/cegui/cegui_logger.hpp>
#include <sge/cegui/scoped_system.hpp>
#include <sge/cegui/resource_provider.hpp>
#include <sge/cegui/image_codec.hpp>
#include <sge/cegui/input.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <sge/time/duration.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace cegui
{
class system
{
FCPPT_NONCOPYABLE(
	system);
public:
	SGE_CEGUI_SYMBOL explicit
	system(
		fcppt::filesystem::path const &,
		fcppt::string const &,
		sge::renderer::device_ptr,
		sge::image2d::multi_loader &,
		sge::charconv::system_ptr,
		sge::systems::instance &,
		sge::input::keyboard::device &,
		sge::input::mouse::device &);

	SGE_CEGUI_SYMBOL void
	update(
		sge::time::duration const &);

	SGE_CEGUI_SYMBOL sge::image2d::multi_loader &
	image_loader() const;

	SGE_CEGUI_SYMBOL sge::renderer::device_ptr const
	renderer() const;

	SGE_CEGUI_SYMBOL fcppt::filesystem::path const
	to_absolute_path(
		CEGUI::String const &,
		CEGUI::String const &);

	SGE_CEGUI_SYMBOL void
	render();

	SGE_CEGUI_SYMBOL ~system();
private:
	fcppt::filesystem::path prefix_;
	cegui_logger cegui_logger_;
	cegui::renderer renderer_;
	image_codec image_codec_;
	resource_provider resource_provider_;
	scoped_system system_;
	input input_;
	fcppt::signal::scoped_connection viewport_change_connection_;
	// We have to memorize the old viewport so we don't call
	// notifyDisplaySizeChanged if old == new (costs performance)
	sge::renderer::pixel_rect old_viewport_;

	void
	viewport_change(
		sge::renderer::device_ptr);
};
}
}

#endif
