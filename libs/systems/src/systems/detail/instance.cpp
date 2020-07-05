//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/config/config_path.hpp>
#include <sge/config/own_app_name.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/log/apply_options.hpp>
#include <sge/log/option_container.hpp>
#include <sge/parse/ini/file_result.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_log_settings.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/detail/instance.hpp>
#include <sge/systems/detail/list.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/impl/any_visitor.hpp>
#include <sge/systems/impl/extract_config.hpp>
#include <sge/systems/impl/extract_plugin_path.hpp>
#include <sge/systems/impl/unpack_if_present.hpp>
#include <sge/systems/impl/detail/instance_impl.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/either/failure_opt.hpp>
#include <fcppt/either/success_opt.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/variant/apply.hpp>


sge::systems::detail::instance::instance(
	sge::systems::detail::list const &_list
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::systems::detail::instance_impl
		>(
			sge::systems::impl::extract_plugin_path(
				_list.get()
			),
			fcppt::optional::bind(
				sge::systems::impl::extract_config(
					_list.get()
				).log_settings(),
				[](
					sge::systems::log_settings const &_settings
				)
				{
					return
						_settings.log_context();
				}
			)
		)
	)
{
	sge::systems::optional_log_settings const log_settings(
		sge::systems::impl::extract_config(
			_list.get()
		)
		.log_settings()
	);

	sge::log::apply_options(
		this->log_context(),
		fcppt::optional::maybe(
			log_settings,
			[]{
				return
					sge::log::option_container{};
			},
			[](
				sge::systems::log_settings const &_settings
			)
			-> sge::log::option_container
			{
				return
					_settings.options();
			}
		)
	);

	sge::parse::ini::file_result const ini_result_value(
		sge::parse::ini::parse_file(
			sge::config::config_path(
				sge::config::own_app_name()
			)
			/
			FCPPT_TEXT("systems.ini")
		)
	);

	fcppt::optional::maybe_void(
		fcppt::either::failure_opt(
			ini_result_value
		),
		[
			this
		](
			fcppt::optional::object<
				fcppt::parse::error<
					char
				>
			> const &_error
		)
		{
			fcppt::optional::maybe_void(
				_error,
				[
					this
				](
					fcppt::parse::error<
						char
					> const &_parse_error
				)
				{
					FCPPT_LOG_ERROR(
						this->impl_->log(),
						fcppt::log::out
							<<
							fcppt::from_std_string(
								_parse_error.get()
							)
					)
				}
			);
		}
	);

	sge::systems::detail::any_map const &map(
		_list.get()
	);

	// Special case:
	// The window system must be initialized before the renderer system.
	sge::systems::impl::unpack_if_present<
		sge::systems::window
	>(
		map,
		sge::systems::detail::any_key::window,
		[
			this
		](
			sge::systems::window const &_window
		)
		{
			// TODO: Take viewport settings into account here
			impl_->init_window_system(
				_window
			);
		}
	);

	// Special case:
	// The renderer system must be initialized before the window.
	sge::systems::impl::unpack_if_present<
		sge::systems::detail::renderer
	>(
		map,
		sge::systems::detail::any_key::renderer,
		[
			this,
			&ini_result_value
		](
			sge::systems::detail::renderer const &_param
		)
		{
			impl_->init_renderer_system(
				_param,
				fcppt::either::success_opt(
					ini_result_value
				)
			);
		}
	);

	for(
		auto const &item
		:
		map
	)
		fcppt::variant::apply(
			sge::systems::impl::any_visitor(
				fcppt::make_ref(
					*impl_
				)
			),
			item.second
		);

	impl_->post_init();
}

sge::systems::detail::instance::~instance()
{
}

fcppt::log::context_reference
sge::systems::detail::instance::log_context() const
{
	return
		impl_->log_context();
}

sge::plugin::manager &
sge::systems::detail::instance::plugin_manager()
{
	return
		impl_->plugin_manager();
}

sge::renderer::core &
sge::systems::detail::instance::renderer_core() const
{
	return
		impl_->renderer_core();
}

sge::renderer::system &
sge::systems::detail::instance::renderer_system() const
{
	return
		impl_->renderer_system();
}

sge::renderer::device::ffp &
sge::systems::detail::instance::renderer_device_ffp() const
{
	return
		impl_->renderer_device_ffp();
}

sge::renderer::device::core &
sge::systems::detail::instance::renderer_device_core() const
{
	return
		impl_->renderer_device_core();
}

sge::input::system &
sge::systems::detail::instance::input_system() const
{
	return
		impl_->input_system();
}

sge::input::processor &
sge::systems::detail::instance::input_processor() const
{
	return
		impl_->input_processor();
}

sge::image2d::system &
sge::systems::detail::instance::image_system() const
{
	return
		impl_->image_system();
}

sge::audio::loader &
sge::systems::detail::instance::audio_loader() const
{
	return
		impl_->audio_loader();
}

sge::audio::player &
sge::systems::detail::instance::audio_player() const
{
	return
		impl_->audio_player();
}

sge::font::system &
sge::systems::detail::instance::font_system() const
{
	return
		impl_->font_system();
}

sge::window::object &
sge::systems::detail::instance::window() const
{
	return
		impl_->window();
}

sge::window::system &
sge::systems::detail::instance::window_system() const
{
	return
		impl_->window_system();
}

sge::viewport::manager &
sge::systems::detail::instance::viewport_manager() const
{
	return
		impl_->viewport_manager();
}
