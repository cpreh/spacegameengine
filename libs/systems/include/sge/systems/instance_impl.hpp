//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_INSTANCE_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_INSTANCE_IMPL_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/instance_decl.hpp>
#include <sge/systems/list_fwd.hpp>
#include <sge/systems/renderer_caps.hpp>
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
#include <fcppt/log/context_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename... Choices
>
template<
	typename Inits
>
sge::systems::instance<
	Choices...
>::instance(
	sge::systems::list<
		Inits
	> &&_list
)
:
	instance_(
		sge::systems::detail::make_list<
			choices_list
		>(
			std::move(
				_list
			)
		)
	)
{
}

template<
	typename... Choices
>
sge::systems::instance<
	Choices...
>::~instance()
= default;

template<
	typename... Choices
>
fcppt::log::context_reference
sge::systems::instance<
	Choices...
>::log_context() const
{
	return
		instance_.log_context();
}

template<
	typename... Choices
>
sge::plugin::manager &
sge::systems::instance<
	Choices...
>::plugin_manager()
{
	return
		instance_.plugin_manager();
}

template<
	typename... Choices
>
sge::renderer::core &
sge::systems::instance<
	Choices...
>::renderer_core() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			choices_list
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.renderer_core();
}

template<
	typename... Choices
>
sge::renderer::system &
sge::systems::instance<
	Choices...
>::renderer_system() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			choices_list
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.renderer_system();
}

template<
	typename... Choices
>
sge::renderer::device::ffp &
sge::systems::instance<
	Choices...
>::renderer_device_ffp() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			choices_list
		>::value,
		"configuration has no renderer"
	);

	static_assert(
		sge::systems::detail::renderer_caps<
			choices_list
		>::value
		==
		sge::systems::renderer_caps::ffp,
		"configuration has no ffp renderer"
	);

	return
		instance_.renderer_device_ffp();
}

template<
	typename... Choices
>
sge::renderer::device::core &
sge::systems::instance<
	Choices...
>::renderer_device_core() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			choices_list
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.renderer_device_core();
}

template<
	typename... Choices
>
sge::input::system &
sge::systems::instance<
	Choices...
>::input_system() const
{
	static_assert(
		sge::systems::detail::has_with_input<
			choices_list
		>::value,
		"configuration has no input"
	);

	return
		instance_.input_system();
}

template<
	typename... Choices
>
sge::input::processor &
sge::systems::instance<
	Choices...
>::input_processor() const
{
	static_assert(
		sge::systems::detail::has_with_input<
			choices_list
		>::value,
		"configuration has no input"
	);

	return
		instance_.input_processor();
}

template<
	typename... Choices
>
sge::image2d::system &
sge::systems::instance<
	Choices...
>::image_system() const
{
	static_assert(
		sge::systems::detail::has_with_image2d<
			choices_list
		>::value,
		"configuration has no image2d system"
	);

	return
		instance_.image_system();
}

template<
	typename... Choices
>
sge::audio::loader &
sge::systems::instance<
	Choices...
>::audio_loader() const
{
	static_assert(
		sge::systems::detail::has_with_audio_loader<
			choices_list
		>::value,
		"configuration has no audio loader"
	);

	return
		instance_.audio_loader();
}

template<
	typename... Choices
>
sge::audio::player &
sge::systems::instance<
	Choices...
>::audio_player() const
{
	static_assert(
		sge::systems::detail::has_with_audio_player<
			choices_list
		>::value,
		"configuration has no audio player"
	);

	return
		instance_.audio_player();
}

template<
	typename... Choices
>
sge::font::system &
sge::systems::instance<
	Choices...
>::font_system() const
{
	static_assert(
		sge::systems::detail::has_with_font<
			choices_list
		>::value,
		"configuration has no font system"
	);

	return
		instance_.font_system();
}

template<
	typename... Choices
>
sge::window::system &
sge::systems::instance<
	Choices...
>::window_system() const
{
	static_assert(
		sge::systems::detail::has_with_window<
			choices_list
		>::value,
		"configuration has no window"
	);

	return
		instance_.window_system();
}

template<
	typename... Choices
>
sge::window::object &
sge::systems::instance<
	Choices...
>::window() const
{
	static_assert(
		sge::systems::detail::has_with_window<
			choices_list
		>::value,
		"configuration has no window"
	);

	return
		instance_.window();
}

template<
	typename... Choices
>
sge::viewport::manager &
sge::systems::instance<
	Choices...
>::viewport_manager() const
{
	static_assert(
		sge::systems::detail::has_with_renderer<
			choices_list
		>::value,
		"configuration has no renderer"
	);

	return
		instance_.viewport_manager();
}

#endif
