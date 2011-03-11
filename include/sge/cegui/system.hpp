#ifndef SGE_CEGUI_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_SYSTEM_HPP_INCLUDED

#include <CEGUI/CEGUIString.h>
#include <sge/cegui/symbol.hpp>
#include <sge/cegui/detail/renderer.hpp>
#include <sge/cegui/detail/cegui_logger.hpp>
#include <sge/cegui/detail/scoped_system.hpp>
#include <sge/cegui/detail/input.hpp>
#include <sge/cegui/detail/resource_provider.hpp>
#include <sge/cegui/detail/image_codec.hpp>
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
		sge::renderer::device_ptr,
		sge::image2d::multi_loader &,
		sge::charconv::system_ptr,
		sge::systems::instance &,
		sge::input::keyboard::device &,
		sge::input::mouse::device &);

	// Sends cegui a time pulse to calculate double clicks, tooltip
	// durations and so on
	SGE_CEGUI_SYMBOL void
	update(
		sge::time::duration const &);

	SGE_CEGUI_SYMBOL void
	render();

	SGE_CEGUI_SYMBOL 
	~system();
private:
	// To keep the user interface clean, we permit access to the image
	// loader and the renderer only to friend classes (see the accessor
	// functions below)
	friend class detail::texture;
	friend class detail::texture_target;

	fcppt::filesystem::path prefix_;
	detail::cegui_logger cegui_logger_;
	detail::renderer renderer_;
	detail::image_codec image_codec_;
	detail::resource_provider resource_provider_;
	detail::scoped_system system_;
	detail::input input_;
	fcppt::signal::scoped_connection viewport_change_connection_;
	// We have to memorize the old viewport so we don't call
	// notifyDisplaySizeChanged if old == new (costs performance)
	sge::renderer::pixel_rect old_viewport_;

	void
	viewport_change(
		sge::renderer::device_ptr);

	SGE_CEGUI_SYMBOL sge::image2d::multi_loader &
	image_loader() const;

	SGE_CEGUI_SYMBOL sge::renderer::device_ptr const
	renderer() const;

	SGE_CEGUI_SYMBOL fcppt::filesystem::path const
	to_absolute_path(
		CEGUI::String const &,
		CEGUI::String const &);
};
}
}

#endif
