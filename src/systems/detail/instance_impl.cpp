/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/log/option_container.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/src/systems/make_scoped_output.hpp>
#include <sge/src/systems/detail/instance_impl.hpp>
#include <sge/src/systems/modules/audio/loader.hpp>
#include <sge/src/systems/modules/audio/player.hpp>
#include <sge/src/systems/modules/font/object.hpp>
#include <sge/src/systems/modules/image2d/object.hpp>
#include <sge/src/systems/modules/input/object.hpp>
#include <sge/src/systems/modules/renderer/device.hpp>
#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/src/systems/modules/window/object_unique_ptr.hpp>
#include <sge/src/systems/modules/window/system.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/optional_log_redirect_path_fwd.hpp>
#include <sge/systems/plugin_path.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/input_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/main/scoped_output.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/assert/optional_error.hpp>


sge::systems::detail::instance_impl::instance_impl(
	sge::systems::plugin_path const &_plugin_path,
	sge::systems::optional_log_redirect_path const &_log_redirect_path
)
:
	scoped_output_(
		sge::systems::make_scoped_output(
			_log_redirect_path
		)
	),
	plugin_cache_(),
	plugin_manager_(
		_plugin_path.get(),
		sge::plugin::optional_cache_ref(
			fcppt::make_ref(
				plugin_cache_
			)
		)
	),
	window_system_(),
	renderer_system_(),
	window_object_(),
	renderer_device_(),
	input_(),
	audio_loader_(),
	audio_player_(),
	image2d_(),
	font_()
{
}

sge::systems::detail::instance_impl::~instance_impl()
{
}

void
sge::systems::detail::instance_impl::init_window_system(
	sge::systems::window const &_parameters
)
{
	window_system_ =
		optional_window_system(
			fcppt::make_unique_ptr<
				sge::systems::modules::window::system
			>(
				_parameters
			)
		);
}

void
sge::systems::detail::instance_impl::init_renderer_system(
	sge::systems::detail::renderer const &_parameters,
	sge::parse::ini::optional_start const &_config,
	sge::log::option_container const &_log_options
)
{
	renderer_system_ =
		optional_renderer_system(
			fcppt::make_unique_ptr<
				sge::systems::modules::renderer::system
			>(
				plugin_manager_.collection<
					sge::renderer::core
				>(),
				_log_options,
				_parameters,
				_config,
				*FCPPT_ASSERT_OPTIONAL_ERROR(
					window_system_
				)
			)
		);
}

void
sge::systems::detail::instance_impl::init_window_object(
	sge::systems::window const &_parameters
)
{
	window_object_ =
		optional_window_object(
			fcppt::make_unique_ptr<
				sge::systems::modules::window::object
			>(
				_parameters,
				*FCPPT_ASSERT_OPTIONAL_ERROR(
					window_system_
				),
				fcppt::optional::deref(
					renderer_system_
				)
			)
		);
}

void
sge::systems::detail::instance_impl::init_renderer(
	sge::systems::detail::renderer const &_param
)
{
	renderer_device_ =
		optional_renderer_device(
			fcppt::make_unique_ptr<
				sge::systems::modules::renderer::device
			>(
				_param,
				*FCPPT_ASSERT_OPTIONAL_ERROR(
					renderer_system_
				),
				*FCPPT_ASSERT_OPTIONAL_ERROR(
					window_object_
				)
			)
		);
}

void
sge::systems::detail::instance_impl::init_input(
	sge::systems::detail::input const &_parameters,
	sge::log::option_container const &_log_options
)
{
	input_ =
		optional_input(
			fcppt::make_unique_ptr<
				sge::systems::modules::input::object
			>(
				plugin_manager_.collection<
					sge::input::system
				>(),
				_log_options,
				_parameters,
				*FCPPT_ASSERT_OPTIONAL_ERROR(
					window_system_
				),
				*FCPPT_ASSERT_OPTIONAL_ERROR(
					window_object_
				)
			)
		);
}

void
sge::systems::detail::instance_impl::init_image2d(
	sge::systems::image2d const &_parameters,
	sge::log::option_container const &_log_options
)
{
	image2d_ =
		optional_image2d(
			fcppt::make_unique_ptr<
				sge::systems::modules::image2d::object
			>(
				plugin_manager_.collection<
					sge::image2d::system
				>(),
				_log_options,
				_parameters
			)
		);
}

void
sge::systems::detail::instance_impl::init_audio_loader(
	sge::systems::audio_loader const &_parameters,
	sge::log::option_container const &_log_options
)
{
	audio_loader_ =
		optional_audio_loader(
			fcppt::make_unique_ptr<
				sge::systems::modules::audio::loader
			>(
				plugin_manager_.collection<
					sge::audio::loader
				>(),
				_log_options,
				_parameters
			)
		);
}

void
sge::systems::detail::instance_impl::init_audio_player(
	sge::systems::audio_player const &_parameters,
	sge::log::option_container const &_log_options
)
{
	audio_player_ =
		optional_audio_player(
			fcppt::make_unique_ptr<
				sge::systems::modules::audio::player
			>(
				plugin_manager_.collection<
					sge::audio::player
				>(),
				_log_options,
				_parameters
			)
		);
}

void
sge::systems::detail::instance_impl::init_font(
	sge::systems::font const &_parameters,
	sge::log::option_container const &_log_options
)
{
	font_ =
		optional_font(
			fcppt::make_unique_ptr<
				sge::systems::modules::font::object
			>(
				plugin_manager_.collection<
					sge::font::system
				>(),
				_log_options,
				_parameters
			)
		);
}

void
sge::systems::detail::instance_impl::post_init()
{
	fcppt::optional::maybe_void(
		window_object_,
		[](
			sge::systems::modules::window::object_unique_ptr const &_window_object
		)
		{
			_window_object->post_init();
		}
	);
}

sge::plugin::manager &
sge::systems::detail::instance_impl::plugin_manager()
{
	return
		plugin_manager_;
}

sge::renderer::core &
sge::systems::detail::instance_impl::renderer_core() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			renderer_system_
		)->core();
}

sge::renderer::system &
sge::systems::detail::instance_impl::renderer_system() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			renderer_system_
		)->get();
}

sge::renderer::device::ffp &
sge::systems::detail::instance_impl::renderer_device_ffp() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			renderer_device_
		)->get_ffp();
}

sge::renderer::device::core &
sge::systems::detail::instance_impl::renderer_device_core() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			renderer_device_
		)->get_core();
}

sge::renderer::device::index
sge::systems::detail::instance_impl::renderer_device_index() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			renderer_device_
		)->index();
}

sge::input::system &
sge::systems::detail::instance_impl::input_system() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			input_
		)->system();
}

sge::input::processor &
sge::systems::detail::instance_impl::input_processor() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			input_
		)->processor();
}

sge::input::focus::object &
sge::systems::detail::instance_impl::focus_collector() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			input_
		)->focus_collector();
}

sge::input::cursor::object &
sge::systems::detail::instance_impl::cursor_demuxer() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			input_
		)->cursor_demuxer();
}

sge::input::keyboard::device &
sge::systems::detail::instance_impl::keyboard_collector() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			input_
		)->keyboard_collector();
}

sge::input::mouse::device &
sge::systems::detail::instance_impl::mouse_collector() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			input_
		)->mouse_collector();
}

sge::image2d::system &
sge::systems::detail::instance_impl::image_system() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			image2d_
		)->system();
}

sge::audio::loader &
sge::systems::detail::instance_impl::audio_loader() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			audio_loader_
		)->get();
}

sge::audio::player &
sge::systems::detail::instance_impl::audio_player() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			audio_player_
		)->get();
}

sge::font::system &
sge::systems::detail::instance_impl::font_system() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			font_
		)->system();
}

sge::window::system &
sge::systems::detail::instance_impl::window_system() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			window_system_
		)->get();
}

sge::window::object &
sge::systems::detail::instance_impl::window() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			window_object_
		)->get();
}

sge::viewport::manager &
sge::systems::detail::instance_impl::viewport_manager() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			renderer_device_
		)->viewport_manager();
}
