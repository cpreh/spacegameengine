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


#include "create_normal_window.hpp"
#include "create_render_window.hpp"
#include "cursor_modifier.hpp"
#include "plugin_path.hpp"
#include "wrap_window.hpp"
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_ptr.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/charconv/plugin.hpp>
#include <sge/charconv/system.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <sge/font/plugin.hpp>
#include <sge/font/system.hpp>
#include <sge/font/system_ptr.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/plugin.hpp>
#include <sge/input/plugin.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_ptr.hpp>
#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/log/global.hpp>
#include <sge/model/plugin.hpp>
#include <sge/model/loader.hpp>
#include <sge/model/loader_ptr.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_ptr.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/instance.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/object_shared_ptr.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_info.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/noncopyable.hpp>
#include <typeinfo>

class sge::systems::instance::impl
{
	FCPPT_NONCOPYABLE(
		impl
	);
public:
	plugin::manager                                 plugin_manager_;

	// unload the plugins last so that any code that still needs them can run
	plugin::object<sge::renderer::system>::ptr_type renderer_plugin_;
	plugin::object<sge::input::system>::ptr_type    input_plugin_;
	plugin::object<audio::player>::ptr_type         audio_player_plugin_;
	plugin::object<charconv::system>::ptr_type      charconv_plugin_;
	plugin::object<font::system>::ptr_type          font_plugin_;
	plugin::object<model::loader>::ptr_type         md3_plugin_;

	fcppt::optional<sge::systems::window>           window_param_;
	awl::system::object_shared_ptr                  window_system_;
	sge::window::instance_ptr                       window_;

	sge::renderer::system_ptr                       renderer_system_;
	sge::renderer::device_ptr                       renderer_;

	typedef fcppt::scoped_ptr<
		sge::viewport::manager
	> viewport_manager_ptr;

	viewport_manager_ptr                            viewport_manager_;

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
		sge::image2d::multi_loader
	> image_multi_loader_ptr;

	image_multi_loader_ptr                          image_multi_loader_;

	typedef fcppt::scoped_ptr<
		sge::audio::multi_loader
	> audio_multi_loader_ptr;

	audio_multi_loader_ptr                          audio_multi_loader_;

	audio::player_ptr                               audio_player_;

	font::system_ptr                                font_system_;

	charconv::system_ptr                            charconv_system_;

	model::loader_ptr                               md3_loader_;

	explicit impl(
		fcppt::filesystem::path const &plugin_path
	);

	~impl();

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
		sge::systems::image_loader const &
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
	init_md3();

	void
	post_init();
private:
	void
	create_window();

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
		sge::systems::image_loader const &
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
		sge::systems::parameterless::type
	) const;
private:
	sge::systems::instance::impl &impl_;
};

}

sge::systems::instance::instance(
	systems::list const &_list
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
	systems::any_set const &set(
		_list.get()
	);

	for(
		systems::any_set::const_iterator it(
			set.begin()
		);
		it != set.end();
		++it
	)
		fcppt::variant::apply_unary(
			::visitor(
				*impl_
			),
			*it
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
	return *impl_->renderer_system_;
}

sge::renderer::device &
sge::systems::instance::renderer() const
{
	return *impl_->renderer_;
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

sge::image2d::multi_loader &
sge::systems::instance::image_loader() const
{
	return *impl_->image_multi_loader_;
}

sge::audio::multi_loader &
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

sge::model::loader &
sge::systems::instance::md3_loader() const
{
	return *impl_->md3_loader_;
}

sge::window::instance &
sge::systems::instance::window() const
{
	return *impl_->window_;
}

sge::viewport::manager &
sge::systems::instance::viewport_manager() const
{
	return *impl_->viewport_manager_;
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
	sge::systems::image_loader const &_param
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
	sge::systems::parameterless::type const _type
) const
{
	switch(
		_type
	)
	{
	case sge::systems::parameterless::charconv:
		impl_.init_charconv();
		return;
	case sge::systems::parameterless::font:
		impl_.init_font();
		return;
	case sge::systems::parameterless::md3_loader:
		impl_.init_md3();
		return;
	}

	throw sge::systems::exception(
		FCPPT_TEXT("Invalid systems::parameterless!")
	);
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
sge::systems::instance::impl::init_renderer(
	sge::systems::renderer const &_param
)
{
	sge::renderer::parameters const &renderer_param(
		_param.parameters()
	);

	renderer_plugin_ = default_plugin<sge::renderer::system>();

	renderer_system_ = renderer_plugin_->get()();

	if(
		!window_
	)
	{
		if(
			!window_param_
		)
			throw sge::systems::exception(
				FCPPT_TEXT("systems: renderer device requested, but no window parameter given!")
			);

		window_ =
			systems::create_render_window(
				window_system_,
				renderer_system_,
				*window_param_,
				renderer_param
			);
	}

	renderer_ =
		renderer_system_->create_renderer(
			renderer_param,
			sge::renderer::adapter(
				0
			),
			*window_
		);
	
	viewport_manager_.take(
		fcppt::make_unique_ptr<
			sge::viewport::manager
		>(
			fcppt::ref(
				*renderer_
			),
			_param.resize_function()
		)
	);
}

void
sge::systems::instance::impl::init_window(
	sge::systems::window const &_window_param
)
{
	if(
		fcppt::variant::holds_type<
			sge::systems::wrapped_window
		>(
			_window_param.parameter()
		)
	)
		window_ =
			sge::systems::wrap_window(
				_window_param
			);
	else
	{
		window_system_ = awl::system::create();

		window_param_ = _window_param;
	}
}

void
sge::systems::instance::impl::init_input(
	systems::input const &_param
)
{
	if(
		!window_
	)
	{
		if(
			!window_param_
		)
			throw sge::systems::exception(
				FCPPT_TEXT("systems: input system requested, but no window parameter given!")
			);

		this->create_window();
	}

	input_plugin_ = default_plugin<sge::input::system>();

	input_system_ = input_plugin_->get()();

	input_processor_ =
		input_system_->create_processor(
			window_
		);

	if(
		_param.input_helpers() & systems::input_helper::cursor_demuxer
	)
		cursor_demuxer_ =
			fcppt::make_shared_ptr<
				sge::input::cursor::demuxer
			>(
				input_processor_
			);

	if(
		_param.input_helpers() & systems::input_helper::keyboard_collector
	)
		keyboard_collector_ =
			fcppt::make_shared_ptr<
				sge::input::keyboard::collector
			>(
				input_processor_
			);
	
	if(
		_param.input_helpers() & systems::input_helper::mouse_collector
	)
		mouse_collector_ =
			fcppt::make_shared_ptr<
				sge::input::mouse::collector
			>(
				input_processor_
			);
	
	if(
		_param.cursor_options()
	)
		cursor_modifier_.take(
			fcppt::make_unique_ptr<
				systems::cursor_modifier
			>(
				input_processor_,
				_param.cursor_options()
			)
		);
}

void
sge::systems::instance::impl::init_image(
	sge::systems::image_loader const &_params
)
{
	image_multi_loader_.take(
		fcppt::make_unique_ptr<
			sge::image2d::multi_loader
		>(
			fcppt::ref(
				plugin_manager_
			),
			_params.extensions(),
			_params.capabilities()
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
			fcppt::ref(
				plugin_manager_
			),
			_params.extensions(),
			_params.capabilities()
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
sge::systems::instance::impl::init_md3()
{
	md3_plugin_ = default_plugin<sge::model::loader>();

	md3_loader_ = md3_plugin_->get()();
}

void
sge::systems::instance::impl::post_init()
{
	if(
		!window_param_
	)
		return;

	if(
		!window_
	)
		this->create_window();

	if(
		window_param_->show()
	)
		window_->show();
}

void
sge::systems::instance::impl::create_window()
{
	window_ =
		sge::systems::create_normal_window(
			window_system_,
			*window_param_
		);
}

template<
	typename T
>
typename sge::plugin::object<T>::ptr_type const
sge::systems::instance::impl::default_plugin()
{
	return plugin_manager_.plugin<T>().load();
}
