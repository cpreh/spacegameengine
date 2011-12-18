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


#ifndef SGE_SRC_SYSTEMS_DETAIL_INSTANCE_IMPL_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_DETAIL_INSTANCE_IMPL_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/src/systems/plugin_cache.hpp>
#include <sge/src/systems/modules/audio/loader_scoped_ptr.hpp>
#include <sge/src/systems/modules/audio/player_scoped_ptr.hpp>
#include <sge/src/systems/modules/charconv/object_scoped_ptr.hpp>
#include <sge/src/systems/modules/font/object_scoped_ptr.hpp>
#include <sge/src/systems/modules/image2d/object_scoped_ptr.hpp>
#include <sge/src/systems/modules/input/object_scoped_ptr.hpp>
#include <sge/src/systems/modules/renderer/device_scoped_ptr.hpp>
#include <sge/src/systems/modules/renderer/system_scoped_ptr.hpp>
#include <sge/src/systems/modules/window/object_scoped_ptr.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/plugin_path.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/instance_impl_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/mainloop/dispatcher_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class instance_impl
{
	FCPPT_NONCOPYABLE(
		instance_impl
	);
public:
	explicit
	instance_impl(
		sge::systems::plugin_path const &
	);

	~instance_impl();

	void
	init_renderer_system(
		sge::systems::renderer const &
	);

	void
	init_renderer(
		sge::systems::renderer const &
	);

	void
	init_window(
		sge::systems::window const &
	);

	void
	init_input(
		sge::systems::input const &
	);

	void
	init_image2d(
		sge::systems::image2d const &
	);

	void
	init_audio_loader(
		sge::systems::audio_loader const &
	);

	void
	init_audio_player(
		sge::systems::audio_player const &
	);

	void
	init_font();

	void
	init_charconv();

	void
	post_init();

	sge::plugin::manager &
	plugin_manager();

	sge::renderer::system &
	renderer_system() const;

	sge::renderer::device &
	renderer_device() const;

	sge::input::system &
	input_system() const;

	sge::input::processor &
	input_processor() const;

	sge::input::cursor::object &
	cursor_demuxer() const;

	sge::input::keyboard::device &
	keyboard_collector() const;

	sge::input::mouse::device &
	mouse_collector() const;

	sge::image2d::system &
	image_system() const;

	sge::audio::loader &
	audio_loader() const;

	sge::audio::player &
	audio_player() const;

	sge::charconv::system &
	charconv_system() const;

	sge::font::system &
	font_system() const;

	sge::window::system &
	window_system() const;

	sge::window::object &
	window() const;

	sge::viewport::manager &
	viewport_manager() const;

	awl::mainloop::dispatcher &
	awl_dispatcher() const;
private:
	sge::plugin::manager plugin_manager_;

	// Almost all plugins need to be unloaded last.
	// If, for example, libGL.so is unloaded before the X window
	// will be destroyed, then the unloading will crash.
	sge::systems::plugin_cache plugin_cache_;

	sge::systems::modules::window::object_scoped_ptr window_;

	sge::systems::modules::renderer::system_scoped_ptr renderer_system_;

	sge::systems::modules::renderer::device_scoped_ptr renderer_device_;

	sge::systems::modules::input::object_scoped_ptr input_;

	sge::systems::modules::audio::loader_scoped_ptr audio_loader_;

	sge::systems::modules::audio::player_scoped_ptr audio_player_;

	sge::systems::modules::image2d::object_scoped_ptr image2d_;

	sge::systems::modules::font::object_scoped_ptr font_;

	sge::systems::modules::charconv::object_scoped_ptr charconv_;
};

}
}
}

#endif
