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


#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/audio/player_ptr.hpp>
#include <sge/charconv/plugin.hpp>
#include <sge/charconv/system.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <sge/font/plugin.hpp>
#include <sge/font/system.hpp>
#include <sge/font/system_ptr.hpp>
#include <sge/image2d/multi_system.hpp>
#include <sge/image2d/multi_system_parameters.hpp>
#include <sge/image2d/plugin.hpp>
#include <sge/input/plugin.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_ptr.hpp>
#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/log/global.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_ptr.hpp>
#include <sge/src/systems/cursor_modifier.hpp>
#include <sge/src/systems/plugin_cache.hpp>
#include <sge/src/systems/plugin_path.hpp>
#include <sge/src/systems/modules/renderer/device.hpp>
#include <sge/src/systems/modules/renderer/device_scoped_ptr.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/src/systems/modules/renderer/system_scoped_ptr.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/src/systems/modules/window/object_scoped_ptr.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player.hpp>
#include <sge/systems/charconv.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/mainloop/dispatcher_fwd.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/object_shared_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_info.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>

#include <sge/renderer/plugin_ptr.hpp>

class sge::systems::instance::impl
{
	FCPPT_NONCOPYABLE(
		impl
	);
public:
	plugin::manager                                 plugin_manager_;

	// Almost all plugins need to be unloaded last.
	// If, for example, libGL.so is unloaded before the X window
	// will be destroyed, then the unloading will crash.
	sge::systems::plugin_cache plugin_cache_;

	plugin::object<sge::input::system>::ptr_type    input_plugin_;
	plugin::object<sge::audio::player>::ptr_type         audio_player_plugin_;
	plugin::object<sge::charconv::system>::ptr_type      charconv_plugin_;
	plugin::object<sge::font::system>::ptr_type          font_plugin_;

	sge::systems::modules::window::object_scoped_ptr window_;

	sge::systems::modules::renderer::system_scoped_ptr renderer_system_;

	sge::systems::modules::renderer::device_scoped_ptr renderer_device_;

	typedef fcppt::scoped_ptr<
		sge::systems::cursor_modifier
	> cursor_modifier;

	sge::input::system_ptr                          input_system_;
	sge::input::processor_ptr                       input_processor_;
	sge::input::cursor::object_ptr                  cursor_demuxer_;
	sge::input::keyboard::device_ptr                keyboard_collector_;
	sge::input::mouse::device_ptr                   mouse_collector_;
	cursor_modifier                                 cursor_modifier_;

	typedef fcppt::scoped_ptr<
		sge::image2d::multi_system
	> image_multi_system_ptr;

	image_multi_system_ptr                          image_multi_system_;

	typedef fcppt::scoped_ptr<
		sge::audio::multi_loader
	> audio_multi_loader_ptr;

	audio_multi_loader_ptr                          audio_multi_loader_;

	sge::audio::player_ptr                               audio_player_;

	sge::font::system_ptr                                font_system_;

	sge::charconv::system_ptr                            charconv_system_;

	explicit impl(
		fcppt::filesystem::path const &plugin_path
	);

	~impl();

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
	init_image(
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
private:
	template<
		typename T
	>
	typename plugin::object<T>::ptr_type const
	default_plugin();
};

namespace
{

class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	);
public:
	typedef void result_type;

	visitor(
		sge::systems::instance::impl &
	);

	result_type
	operator()(
		sge::systems::config const &
	) const;

	result_type
	operator()(
		sge::systems::renderer const &
	) const;

	result_type
	operator()(
		sge::systems::window const &
	) const;

	result_type
	operator()(
		sge::systems::image2d const &
	) const;

	result_type
	operator()(
		sge::systems::audio_loader const &
	) const;

	result_type
	operator()(
		sge::systems::audio_player const &
	) const;

	result_type
	operator()(
		sge::systems::input const &
	) const;

	result_type
	operator()(
		sge::systems::charconv const &
	) const;

	result_type
	operator()(
		sge::systems::font const &
	) const;
private:
	sge::systems::instance::impl &impl_;
};

}

sge::systems::instance::instance(
	sge::systems::list const &_list
)
:
	impl_(
		fcppt::make_unique_ptr<
			impl
		>(
			sge::systems::plugin_path(
				_list.get()
			)
		)
	)
{
	sge::systems::any_map const &map(
		_list.get()
	);

	// Special case:
	// The renderer system must be initialized before the window,
	// but the window must be initialized before a renderer device
	{
		sge::systems::any_map::const_iterator const it(
			map.find(
				sge::systems::any_key::renderer
			)
		);

		if(
			it != map.end()
		)
			impl_->init_renderer_system(
				it->second.get<
					sge::systems::renderer
				>()
			);
	}

	for(
		sge::systems::any_map::const_iterator it(
			map.begin()
		);
		it != map.end();
		++it
	)
		fcppt::variant::apply_unary(
			::visitor(
				*impl_
			),
			it->second
		);

	impl_->post_init();
}

sge::systems::instance::~instance()
{
}

sge::plugin::manager &
sge::systems::instance::plugin_manager()
{
	return impl_->plugin_manager_;
}

sge::renderer::system &
sge::systems::instance::renderer_system() const
{
	return impl_->renderer_system_->get();
}

sge::renderer::device &
sge::systems::instance::renderer() const
{
	return impl_->renderer_device_->get();
}

sge::input::system &
sge::systems::instance::input_system() const
{
	return *impl_->input_system_;
}

sge::input::processor &
sge::systems::instance::input_processor() const
{
	return *impl_->input_processor_;
}

sge::input::cursor::object &
sge::systems::instance::cursor_demuxer() const
{
	return *impl_->cursor_demuxer_;
}

sge::input::keyboard::device &
sge::systems::instance::keyboard_collector() const
{
	return *impl_->keyboard_collector_;
}

sge::input::mouse::device &
sge::systems::instance::mouse_collector() const
{
	return *impl_->mouse_collector_;
}

sge::image2d::system &
sge::systems::instance::image_system() const
{
	return *impl_->image_multi_system_;
}

sge::audio::loader &
sge::systems::instance::audio_loader() const
{
	return *impl_->audio_multi_loader_;
}

sge::audio::player &
sge::systems::instance::audio_player() const
{
	return *impl_->audio_player_;
}

sge::charconv::system &
sge::systems::instance::charconv_system() const
{
	return *impl_->charconv_system_;
}

sge::font::system &
sge::systems::instance::font_system() const
{
	return *impl_->font_system_;
}

sge::window::object &
sge::systems::instance::window() const
{
	return impl_->window_->window();
}

sge::window::system &
sge::systems::instance::window_system() const
{
	return impl_->window_->system();
}

sge::viewport::manager &
sge::systems::instance::viewport_manager() const
{
	return impl_->renderer_device_->viewport_manager();
}

awl::mainloop::dispatcher &
sge::systems::instance::awl_dispatcher() const
{
	return impl_->window_->awl_dispatcher();
}

namespace
{

visitor::visitor(
	sge::systems::instance::impl &_impl
)
:
	impl_(_impl)
{}

visitor::result_type
visitor::operator()(
	sge::systems::config const &
) const
{
}

visitor::result_type
visitor::operator()(
	sge::systems::renderer const &_param
) const
{
	impl_.init_renderer(
		_param
	);
}

visitor::result_type
visitor::operator()(
	sge::systems::window const &_param
) const
{
	impl_.init_window(
		_param
	);
}

visitor::result_type
visitor::operator()(
	sge::systems::image2d const &_param
) const
{
	impl_.init_image(
		_param
	);
}

visitor::result_type
visitor::operator()(
	sge::systems::audio_loader const &_param
) const
{
	impl_.init_audio_loader(
		_param
	);
}

visitor::result_type
visitor::operator()(
	sge::systems::audio_player const &_param
) const
{
	impl_.init_audio_player(
		_param
	);
}

visitor::result_type
visitor::operator()(
	sge::systems::input const &_param
) const
{
	impl_.init_input(
		_param
	);
}

visitor::result_type
visitor::operator()(
	sge::systems::charconv const &
) const
{
	impl_.init_charconv();
}

visitor::result_type
visitor::operator()(
	sge::systems::font const &
) const
{
	impl_.init_font();
}

}

sge::systems::instance::impl::impl(
	fcppt::filesystem::path const &_plugin_path
)
:
	plugin_manager_(
		_plugin_path
	)
{
}

sge::systems::instance::impl::~impl()
{
}

void
sge::systems::instance::impl::init_renderer_system(
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
			fcppt::cref(
				_param
			),
			fcppt::ref(
				plugin_manager_
			)
		)
	);
}

void
sge::systems::instance::impl::init_renderer(
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
sge::systems::instance::impl::init_window(
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
sge::systems::instance::impl::init_input(
	systems::input const &_param
)
{
	FCPPT_ASSERT_PRE(
		window_
	);

	input_plugin_ = default_plugin<sge::input::system>();

	input_system_ = input_plugin_->get()();

	input_processor_ =
		input_system_->create_processor(
			window_->window(),
			window_->system()
		);

	if(
		_param.input_helpers() & systems::input_helper::cursor_demuxer
	)
		cursor_demuxer_ =
			fcppt::make_shared_ptr<
				sge::input::cursor::demuxer
			>(
				fcppt::ref(
					*input_processor_
				)
			);

	if(
		_param.input_helpers() & systems::input_helper::keyboard_collector
	)
		keyboard_collector_ =
			fcppt::make_shared_ptr<
				sge::input::keyboard::collector
			>(
				fcppt::ref(
					*input_processor_
				)
			);

	if(
		_param.input_helpers() & systems::input_helper::mouse_collector
	)
		mouse_collector_ =
			fcppt::make_shared_ptr<
				sge::input::mouse::collector
			>(
				fcppt::ref(
					*input_processor_
				)
			);

	if(
		_param.cursor_options()
	)
		cursor_modifier_.take(
			fcppt::make_unique_ptr<
				systems::cursor_modifier
			>(
				fcppt::ref(
					*input_processor_
				),
				_param.cursor_options()
			)
		);
}

void
sge::systems::instance::impl::init_image(
	sge::systems::image2d const &_params
)
{
	image_multi_system_.take(
		fcppt::make_unique_ptr<
			sge::image2d::multi_system
		>(
			sge::image2d::multi_system_parameters(
				fcppt::ref(
					plugin_manager_
				),
				_params.extensions(),
				_params.capabilities()
			)
		)
	);
}

void
sge::systems::instance::impl::init_audio_loader(
	sge::systems::audio_loader const &_params
)
{
	audio_multi_loader_.take(
		fcppt::make_unique_ptr<
			sge::audio::multi_loader
		>(
			sge::audio::multi_loader_parameters(
				fcppt::ref(
					plugin_manager_
				),
				_params.extensions(),
				_params.capabilities()
			)
		)
	);
}

void
sge::systems::instance::impl::init_audio_player(
	sge::systems::audio_player const &_param
)
{
	for(
		plugin::iterator<sge::audio::player> it(
			plugin_manager_.begin<sge::audio::player>()
		);
		it != plugin_manager_.end<sge::audio::player>();
		++it
	)
	{
		typedef sge::plugin::context<
			sge::audio::player
		>::ptr_type plugin_ptr;

		plugin_ptr const plugin(
			it->load()
		);

		sge::audio::player_ptr const player(
			plugin->get()()
		);

		if(
			player->capabilities() == _param.capabilities()
		)
		{
			audio_player_plugin_ = plugin;

			audio_player_ = audio_player_plugin_->get()();

			return;
		}
	}

	FCPPT_LOG_WARNING(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("No audio player satisfied the audio player capabilities.")
			<< FCPPT_TEXT(" Trying to use the default audio plugin.")
	);

	audio_player_plugin_ = default_plugin<sge::audio::player>();

	audio_player_ = audio_player_plugin_->get()();
}

void
sge::systems::instance::impl::init_font()
{
	this->init_charconv();

	font_plugin_ = default_plugin<sge::font::system>();

	font_system_ =
		font_plugin_->get()(
			charconv_system_
		);
}

void
sge::systems::instance::impl::init_charconv()
{
	if(
		charconv_plugin_
	)
		return;

	charconv_plugin_ = default_plugin<sge::charconv::system>();

	charconv_system_ = charconv_plugin_->get()();
}

void
sge::systems::instance::impl::post_init()
{
	if(
		window_
	)
		window_->post_init();
}

template<
	typename T
>
typename sge::plugin::object<T>::ptr_type const
sge::systems::instance::impl::default_plugin()
{
	return plugin_manager_.plugin<T>().load();
}
