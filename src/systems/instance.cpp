/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/device.hpp>
#include <sge/input/system_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/input/plugin.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/image/multi_loader.hpp>
#include <sge/image/plugin.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/collision/system.hpp>
#include <sge/collision/plugin.hpp>
#include <sge/font/system.hpp>
#include <sge/font/plugin.hpp>
#include <sge/model/plugin.hpp>
#include <sge/model/loader.hpp>
#include <sge/model/loader_ptr.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/create.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_info.hpp>
#include <fcppt/nonassignable.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

class sge::systems::instance::impl
{
public:
	plugin::manager                                 plugin_manager_;

	plugin::object<sge::renderer::system>::ptr_type renderer_plugin_;
	sge::renderer::system_ptr                       renderer_system_;
	sge::renderer::device_ptr                       renderer_;

	plugin::object<sge::input::system>::ptr_type    input_plugin_;
	sge::input::system_ptr                          input_system_;
	sge::input::processor_ptr                       input_processor_;
	sge::input::keyboard::device_ptr                keyboard_collector_;
	sge::input::mouse::device_ptr                   mouse_collector_;

	typedef fcppt::scoped_ptr<
		sge::image::multi_loader
	> image_multi_loader_ptr;

	image_multi_loader_ptr                          image_multi_loader_;

	typedef fcppt::scoped_ptr<
		sge::audio::multi_loader
	> audio_multi_loader_ptr;

	audio_multi_loader_ptr                          audio_multi_loader_;

	plugin::object<audio::player>::ptr_type         audio_player_plugin_;
	audio::player_ptr                               audio_player_;

	plugin::object<collision::system>::ptr_type     collision_plugin_;
	collision::system_ptr                           collision_system_;

	plugin::object<font::system>::ptr_type          font_plugin_;
	font::system_ptr                                font_system_;

	plugin::object<model::loader>::ptr_type         md3_plugin_;
	model::loader_ptr                               md3_loader_;

	window::instance_ptr                            window_;

	fcppt::optional<window::parameters>             window_param_;

	void
	init_renderer(
		renderer::parameters const &
	);

	void
	init_window(
		window::parameters const &
	);

	void
	init_input(
		sge::systems::input const &
	);

	void
	init_collision_system();

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
	)
public:
	typedef void result_type;

	visitor(
		sge::systems::instance::impl &
	);

	result_type
	operator()(
		sge::renderer::parameters const &
	) const;

	result_type
	operator()(
		sge::window::parameters const &
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
	list const &_list
)
:
	impl_(
		fcppt::make_unique_ptr<
			impl
		>()
	)
{
	reinit(
		_list
	);
}

sge::systems::instance::~instance()
{
}

void
sge::systems::instance::reinit(
	systems::list const &_list
)
{
	BOOST_FOREACH(
		sge::systems::any const &elem,
		_list.get()
	)
		fcppt::variant::apply_unary(
			::visitor(
				*impl_
			),
			elem
		);
	
	impl_->post_init();
}

sge::plugin::manager &
sge::systems::instance::plugin_manager()
{
	return impl_->plugin_manager_;
}

sge::renderer::system_ptr const
sge::systems::instance::renderer_system() const
{
	return impl_->renderer_system_;
}

sge::renderer::device_ptr const
sge::systems::instance::renderer() const
{
	return impl_->renderer_;
}

sge::input::system_ptr const
sge::systems::instance::input_system() const
{
	return impl_->input_system_;
}

sge::input::processor_ptr const
sge::systems::instance::input_processor() const
{
	return impl_->input_processor_;
}

sge::input::keyboard::device_ptr const
sge::systems::instance::keyboard_collector() const
{
	return impl_->keyboard_collector_;
}

sge::input::mouse::device_ptr const
sge::systems::instance::mouse_collector() const
{
	return impl_->mouse_collector_;
}

sge::image::multi_loader &
sge::systems::instance::image_loader() const
{
	return *impl_->image_multi_loader_;
}

sge::audio::multi_loader &
sge::systems::instance::audio_loader() const
{
	return *impl_->audio_multi_loader_;
}

sge::audio::player_ptr const
sge::systems::instance::audio_player() const
{
	return impl_->audio_player_;
}

sge::collision::system_ptr const
sge::systems::instance::collision_system() const
{
	return impl_->collision_system_;
}

sge::font::system_ptr const
sge::systems::instance::font_system() const
{
	return impl_->font_system_;
}

sge::model::loader_ptr const
sge::systems::instance::md3_loader() const
{
	return impl_->md3_loader_;
}

sge::window::instance_ptr const
sge::systems::instance::window() const
{
	return impl_->window_;
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
	sge::renderer::parameters const &_param
) const
{
	impl_.init_renderer(
		_param
	);
}

visitor::result_type
visitor::operator()(
	sge::window::parameters const &_param
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
	case sge::systems::parameterless::collision_system:
		impl_.init_collision_system();
		return;
	case sge::systems::parameterless::font:
		impl_.init_font();
		return;
	case sge::systems::parameterless::md3_loader:
		impl_.init_md3();
		return;
	}

	throw sge::exception(
		FCPPT_TEXT("Invalid systems::parameterless!")
	);
}

}

void
sge::systems::instance::impl::init_window(
	window::parameters const &_window_param
)
{
	window_param_ = _window_param;
}

void
sge::systems::instance::impl::init_renderer(
	renderer::parameters const &_param
)
{
	renderer_plugin_ = default_plugin<renderer::system>();

	renderer_system_.reset(
		renderer_plugin_->get()()
	);

	if(!window_)
	{
		if(!window_param_)
			throw sge::exception(
				FCPPT_TEXT("systems: renderer device requested, but no window parameter given!")
			);

		if(!window_param_->dim())
			window_param_->dim(
				_param.display_mode().size()
			);

		window_ =
			renderer_system_->create_window(
				*window_param_,
				_param
			);
	}

	renderer_ =
		renderer_system_->create_renderer(
			_param,
			static_cast<renderer::adapter_type>(0),
			window_
		);
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
			throw sge::exception(
				FCPPT_TEXT("systems: input system requested, but no window parameter given!")
			);

		create_window();
	}

	input_plugin_ = default_plugin<sge::input::system>();

	input_system_.reset(
		input_plugin_->get()()
	);

	input_processor_ =
		input_system_->create_processor(
			window_
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
}

void
sge::systems::instance::impl::init_collision_system()
{
	collision_plugin_ = default_plugin<sge::collision::system>();

	collision_system_.reset(
		collision_plugin_->get()()
	);
}

void
sge::systems::instance::impl::init_image(
	sge::systems::image_loader const &_params
)
{
	image_multi_loader_.take(
		fcppt::make_unique_ptr<
			sge::image::multi_loader
		>(
			std::tr1::ref(
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
			std::tr1::ref(
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
			
			audio_player_.reset(
				audio_player_plugin_->get()()
			);

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

	audio_player_.reset(
		audio_player_plugin_->get()()
	);
}

void
sge::systems::instance::impl::init_font()
{
	font_plugin_ = default_plugin<sge::font::system>();

	font_system_.reset(
		font_plugin_->get()()
	);
}

void
sge::systems::instance::impl::init_md3()
{
	md3_plugin_ = default_plugin<sge::model::loader>();

	md3_loader_.reset(
		md3_plugin_->get()()
	);
}

void
sge::systems::instance::impl::post_init()
{
	if(
		window_param_ && !window_
	)
		create_window();
}

void
sge::systems::instance::impl::create_window()
{
	window_ = sge::window::create(
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
