//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_DETAIL_INSTANCE_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_DETAIL_INSTANCE_IMPL_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/plugin/cache.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/optional_log_context_ref_fwd.hpp>
#include <sge/systems/plugin_path.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/instance_impl_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/log_context.hpp>
#include <sge/systems/impl/audio/loader_unique_ptr.hpp>
#include <sge/systems/impl/audio/player_unique_ptr.hpp>
#include <sge/systems/impl/font/object_unique_ptr.hpp>
#include <sge/systems/impl/image2d/object_unique_ptr.hpp>
#include <sge/systems/impl/input/object_unique_ptr.hpp>
#include <sge/systems/impl/renderer/device_unique_ptr.hpp>
#include <sge/systems/impl/renderer/system_unique_ptr.hpp>
#include <sge/systems/impl/window/object_unique_ptr.hpp>
#include <sge/systems/impl/window/system_unique_ptr.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge::systems::detail
{

class instance_impl
{
	FCPPT_NONMOVABLE(
		instance_impl
	);
public:
	instance_impl(
		sge::systems::plugin_path const &,
		sge::systems::optional_log_context_ref const &
	);

	~instance_impl();

	void
	init_window_system(
		sge::systems::window const &
	);

	void
	init_renderer_system(
		sge::systems::detail::renderer const &,
		sge::parse::ini::optional_start const &
	);

	void
	init_window_object(
		sge::systems::window const &
	);

	void
	init_renderer(
		sge::systems::detail::renderer const &
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
	init_font(
		sge::systems::font const &
	);

	void
	post_init();

	[[nodiscard]]
	fcppt::log::context_reference
	log_context();

	[[nodiscard]]
	fcppt::log::object &
	log();

	[[nodiscard]]
	sge::plugin::manager &
	plugin_manager();

	[[nodiscard]]
	sge::renderer::core &
	renderer_core() const;

	[[nodiscard]]
	sge::renderer::system &
	renderer_system() const;

	[[nodiscard]]
	sge::renderer::device::ffp &
	renderer_device_ffp() const;

	[[nodiscard]]
	sge::renderer::device::core &
	renderer_device_core() const;

	[[nodiscard]]
	sge::input::system &
	input_system() const;

	[[nodiscard]]
	sge::input::processor &
	input_processor() const;

	[[nodiscard]]
	sge::image2d::system &
	image_system() const;

	[[nodiscard]]
	sge::audio::loader &
	audio_loader() const;

	[[nodiscard]]
	sge::audio::player &
	audio_player() const;

	[[nodiscard]]
	sge::font::system &
	font_system() const;

	[[nodiscard]]
	sge::window::system &
	window_system() const;

	[[nodiscard]]
	sge::window::object &
	window() const;

	[[nodiscard]]
	sge::viewport::manager &
	viewport_manager() const;
private:
	sge::systems::impl::log_context log_context_;

	fcppt::log::object log_;

	// Almost all plugins need to be unloaded last. If, for example,
	// libGL.so is unloaded before the X window will be destroyed, then the
	// unloading will crash.
	sge::plugin::cache plugin_cache_;

	sge::plugin::manager plugin_manager_;

	using
	optional_window_system
	=
	fcppt::optional::object<
		sge::systems::impl::window::system_unique_ptr
	>;

	optional_window_system window_system_;

	using
	optional_renderer_system
	=
	fcppt::optional::object<
		sge::systems::impl::renderer::system_unique_ptr
	>;

	optional_renderer_system renderer_system_;

	using
	optional_window_object
	=
	fcppt::optional::object<
		sge::systems::impl::window::object_unique_ptr
	>;

	optional_window_object window_object_;

	using
	optional_renderer_device
	=
	fcppt::optional::object<
		sge::systems::impl::renderer::device_unique_ptr
	>;

	optional_renderer_device renderer_device_;

	using
	optional_input
	=
	fcppt::optional::object<
		sge::systems::impl::input::object_unique_ptr
	>;

	optional_input input_;

	using
	optional_audio_loader
	=
	fcppt::optional::object<
		sge::systems::impl::audio::loader_unique_ptr
	>;

	optional_audio_loader audio_loader_;

	using
	optional_audio_player
	=
	fcppt::optional::object<
		sge::systems::impl::audio::player_unique_ptr
	>;

	optional_audio_player audio_player_;

	using
	optional_image2d
	=
	fcppt::optional::object<
		sge::systems::impl::image2d::object_unique_ptr
	>;

	optional_image2d image2d_;

	using
	optional_font
	=
	fcppt::optional::object<
		sge::systems::impl::font::object_unique_ptr
	>;

	optional_font font_;
};

}

#endif
