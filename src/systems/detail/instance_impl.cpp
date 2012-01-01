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
#include <sge/src/systems/detail/instance_impl.hpp>
#include <sge/src/systems/modules/audio/loader.hpp>
#include <sge/src/systems/modules/audio/player.hpp>
#include <sge/src/systems/modules/charconv/object.hpp>
#include <sge/src/systems/modules/font/object.hpp>
#include <sge/src/systems/modules/image2d/object.hpp>
#include <sge/src/systems/modules/input/object.hpp>
#include <sge/src/systems/modules/renderer/device.hpp>
#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/plugin_path.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/mainloop/dispatcher_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/pre.hpp>


sge::systems::detail::instance_impl::instance_impl(
	sge::systems::plugin_path const &_plugin_path
)
:
	plugin_manager_(
		_plugin_path.get()
	),
	plugin_cache_(),
	window_(),
	renderer_system_(),
	renderer_device_(),
	input_(),
	audio_loader_(),
	audio_player_(),
	image2d_(),
	font_(),
	charconv_()
{
}

sge::systems::detail::instance_impl::~instance_impl()
{
}

void
sge::systems::detail::instance_impl::init_renderer_system(
	sge::systems::renderer const &_param
)
{
	renderer_system_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::renderer::system
		>(
			fcppt::ref(
				plugin_cache_
			),
			fcppt::ref(
				plugin_manager_
			),
			fcppt::cref(
				_param
			)
		)
	);
}

void
sge::systems::detail::instance_impl::init_renderer(
	sge::systems::renderer const &_param
)
{
	FCPPT_ASSERT_PRE(
		window_
	);

	renderer_device_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::renderer::device
		>(
			fcppt::cref(
				_param
			),
			fcppt::ref(
				*renderer_system_
			),
			fcppt::ref(
				*window_
			)
		)
	);
}

void
sge::systems::detail::instance_impl::init_window(
	sge::systems::window const &_window_param
)
{
	window_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::window::object
		>(
			fcppt::cref(
				_window_param
			),
			renderer_system_
			?
				sge::systems::modules::renderer::optional_system_ref(
					*renderer_system_
				)
			:
				sge::systems::modules::renderer::optional_system_ref()
		)
	);
}

void
sge::systems::detail::instance_impl::init_input(
	systems::input const &_parameters
)
{
	FCPPT_ASSERT_PRE(
		window_
	);

	input_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::input::object
		>(
			fcppt::ref(
				plugin_cache_
			),
			fcppt::ref(
				plugin_manager_
			),
			fcppt::cref(
				_parameters
			),
			fcppt::cref(
				*window_
			)
		)
	);
}

void
sge::systems::detail::instance_impl::init_image2d(
	sge::systems::image2d const &_parameters
)
{
	image2d_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::image2d::object
		>(
			fcppt::ref(
				plugin_manager_
			),
			fcppt::cref(
				_parameters
			)
		)
	);
}

void
sge::systems::detail::instance_impl::init_audio_loader(
	sge::systems::audio_loader const &_parameters
)
{
	audio_loader_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::audio::loader
		>(
			fcppt::ref(
				plugin_manager_
			),
			fcppt::cref(
				_parameters
			)
		)
	);
}

void
sge::systems::detail::instance_impl::init_audio_player(
	sge::systems::audio_player const &_parameters
)
{
	audio_player_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::audio::player
		>(
			fcppt::ref(
				plugin_manager_
			),
			fcppt::cref(
				_parameters
			)
		)
	);
}

void
sge::systems::detail::instance_impl::init_font()
{
	this->init_charconv();

	font_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::font::object
		>(
			fcppt::ref(
				plugin_manager_
			),
			fcppt::cref(
				*charconv_
			)
		)
	);
}

void
sge::systems::detail::instance_impl::init_charconv()
{
	if(
		charconv_
	)
		return;

	charconv_.take(
		fcppt::make_unique_ptr<
			sge::systems::modules::charconv::object
		>(
			fcppt::ref(
				plugin_manager_
			)
		)
	);
}

void
sge::systems::detail::instance_impl::post_init()
{
	if(
		window_
	)
		window_->post_init();
}

sge::plugin::manager &
sge::systems::detail::instance_impl::plugin_manager()
{
	return plugin_manager_;
}

sge::renderer::system &
sge::systems::detail::instance_impl::renderer_system() const
{
	return renderer_system_->get();
}

sge::renderer::device &
sge::systems::detail::instance_impl::renderer_device() const
{
	return renderer_device_->get();
}

sge::input::system &
sge::systems::detail::instance_impl::input_system() const
{
	return input_->system();
}

sge::input::processor &
sge::systems::detail::instance_impl::input_processor() const
{
	return input_->processor();
}

sge::input::cursor::object &
sge::systems::detail::instance_impl::cursor_demuxer() const
{
	return input_->cursor_demuxer();
}

sge::input::keyboard::device &
sge::systems::detail::instance_impl::keyboard_collector() const
{
	return input_->keyboard_collector();
}

sge::input::mouse::device &
sge::systems::detail::instance_impl::mouse_collector() const
{
	return input_->mouse_collector();
}

sge::image2d::system &
sge::systems::detail::instance_impl::image_system() const
{
	return image2d_->system();
}

sge::audio::loader &
sge::systems::detail::instance_impl::audio_loader() const
{
	return audio_loader_->get();
}

sge::audio::player &
sge::systems::detail::instance_impl::audio_player() const
{
	return audio_player_->get();
}

sge::charconv::system &
sge::systems::detail::instance_impl::charconv_system() const
{
	return charconv_->system();
}

sge::font::system &
sge::systems::detail::instance_impl::font_system() const
{
	return font_->system();
}

sge::window::system &
sge::systems::detail::instance_impl::window_system() const
{
	return window_->system();
}

sge::window::object &
sge::systems::detail::instance_impl::window() const
{
	return window_->window();
}

sge::viewport::manager &
sge::systems::detail::instance_impl::viewport_manager() const
{
	return renderer_device_->viewport_manager();
}

awl::mainloop::dispatcher &
sge::systems::detail::instance_impl::awl_dispatcher() const
{
	return window_->awl_dispatcher();
}
