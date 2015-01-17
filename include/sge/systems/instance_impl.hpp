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


#ifndef SGE_SYSTEMS_INSTANCE_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_INSTANCE_IMPL_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/systems/cursor_demuxer_fwd.hpp>
#include <sge/systems/instance_decl.hpp>
#include <sge/systems/keyboard_collector_fwd.hpp>
#include <sge/systems/list_fwd.hpp>
#include <sge/systems/mouse_collector_fwd.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/detail/has_input_option.hpp>
#include <sge/systems/detail/has_with_audio_loader.hpp>
#include <sge/systems/detail/has_with_audio_player.hpp>
#include <sge/systems/detail/has_with_font.hpp>
#include <sge/systems/detail/has_with_image2d.hpp>
#include <sge/systems/detail/has_with_input.hpp>
#include <sge/systems/detail/has_with_renderer.hpp>
#include <sge/systems/detail/has_with_window.hpp>
#include <sge/systems/detail/make_list.hpp>
#include <sge/systems/detail/renderer_caps.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>


template<
	typename Choices
>
template<
	typename Inits
>
sge::systems::instance<
	Choices
>::instance(
	sge::systems::list<
		Inits
	> const &_list
)
:
	instance_(
		sge::systems::detail::make_list<
			Choices
		>(
			_list
		)
	)
{
}

template<
	typename Choices
>
sge::systems::instance<
	Choices
>::~instance()
{
}

template<
	typename Choices
>
sge::plugin::manager &
sge::systems::instance<
	Choices
>::plugin_manager()
{
	return
		instance_.plugin_manager();
}

template<
	typename Choices
>
sge::renderer::core &
sge::systems::instance<
	Choices
>::renderer_core() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			Choices
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.renderer_core();
}

template<
	typename Choices
>
sge::renderer::system &
sge::systems::instance<
	Choices
>::renderer_system() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			Choices
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.renderer_system();
}

template<
	typename Choices
>
sge::renderer::device::ffp &
sge::systems::instance<
	Choices
>::renderer_device_ffp() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			Choices
		>::value,
		"configuration has no renderer"
	);

	static_assert(
		sge::systems::detail::renderer_caps<
			Choices
		>::value
		==
		sge::systems::renderer_caps::ffp,
		"configuration has no ffp renderer"
	);

	return
		instance_.renderer_device_ffp();
}

template<
	typename Choices
>
sge::renderer::device::core &
sge::systems::instance<
	Choices
>::renderer_device_core() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			Choices
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.renderer_device_core();
}

template<
	typename Choices
>
sge::renderer::device::index const
sge::systems::instance<
	Choices
>::renderer_device_index() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			Choices
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.renderer_device_index();
}

template<
	typename Choices
>
sge::input::system &
sge::systems::instance<
	Choices
>::input_system() const
{
	static_assert(
		sge::systems::detail::has_with_input<
			Choices
		>::value,
		"configuration has no input"
	);

	return
		instance_.input_system();
}

template<
	typename Choices
>
sge::input::processor &
sge::systems::instance<
	Choices
>::input_processor() const
{
	static_assert(
		sge::systems::detail::has_with_input<
			Choices
		>::value,
		"configuration has no input"
	);

	return
		instance_.input_processor();
}

template<
	typename Choices
>
sge::input::cursor::object &
sge::systems::instance<
	Choices
>::cursor_demuxer() const
{
	static_assert(
		sge::systems::detail::has_with_input<
			Choices
		>::value,
		"configuration has no input"
	);

	static_assert(
		sge::systems::detail::has_input_option<
			Choices,
			sge::systems::cursor_demuxer
		>::value,
		"configuration has no cursor demuxer"
	);

	return
		instance_.cursor_demuxer();
}

template<
	typename Choices
>
sge::input::keyboard::device &
sge::systems::instance<
	Choices
>::keyboard_collector() const
{
	static_assert(
		sge::systems::detail::has_with_input<
			Choices
		>::value,
		"configuration has no input"
	);

	static_assert(
		sge::systems::detail::has_input_option<
			Choices,
			sge::systems::keyboard_collector
		>::value,
		"configuration has no keyboard collector"
	);

	return
		instance_.keyboard_collector();
}

template<
	typename Choices
>
sge::input::mouse::device &
sge::systems::instance<
	Choices
>::mouse_collector() const
{
	static_assert(
		sge::systems::detail::has_with_input<
			Choices
		>::value,
		"configuration has no input"
	);

	static_assert(
		sge::systems::detail::has_input_option<
			Choices,
			sge::systems::mouse_collector
		>::value,
		"configuration has no mouse collector"
	);

	return
		instance_.mouse_collector();
}

template<
	typename Choices
>
sge::image2d::system &
sge::systems::instance<
	Choices
>::image_system() const
{
	static_assert(
		sge::systems::detail::has_with_image2d<
			Choices
		>::value,
		"configuration has no image2d system"
	);

	return
		instance_.image_system();
}

template<
	typename Choices
>
sge::audio::loader &
sge::systems::instance<
	Choices
>::audio_loader() const
{
	static_assert(
		sge::systems::detail::has_with_audio_loader<
			Choices
		>::value,
		"configuration has no audio loader"
	);

	return
		instance_.audio_loader();
}

template<
	typename Choices
>
sge::audio::player &
sge::systems::instance<
	Choices
>::audio_player() const
{
	static_assert(
		sge::systems::detail::has_with_audio_player<
			Choices
		>::value,
		"configuration has no audio player"
	);

	return
		instance_.audio_player();
}

template<
	typename Choices
>
sge::font::system &
sge::systems::instance<
	Choices
>::font_system() const
{
	static_assert(
		sge::systems::detail::has_with_font<
			Choices
		>::value,
		"configuration has no font system"
	);

	return
		instance_.font_system();
}

template<
	typename Choices
>
sge::window::system &
sge::systems::instance<
	Choices
>::window_system() const
{
	static_assert(
		sge::systems::detail::has_with_window<
			Choices
		>::value,
		"configuration has no window"
	);

	return
		instance_.window_system();
}

template<
	typename Choices
>
sge::window::object &
sge::systems::instance<
	Choices
>::window() const
{
	static_assert(
		sge::systems::detail::has_with_window<
			Choices
		>::value,
		"configuration has no window"
	);

	return
		instance_.window();
}

template<
	typename Choices
>
sge::viewport::manager &
sge::systems::instance<
	Choices
>::viewport_manager() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			Choices
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.viewport_manager();
}

#endif
