/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/input/system.hpp>
#include <sge/input/plugin.hpp>
#include <sge/image/multi_loader.hpp>
#include <sge/image/plugin.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/collision/system.hpp>
#include <sge/collision/plugin.hpp>
#include <sge/font/system.hpp>
#include <sge/font/plugin.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/create.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_info.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

class sge::systems::instance::impl
{
public:
	plugin::manager                                 plugin_manager;

	plugin::object<sge::renderer::system>::ptr_type renderer_plugin;
	sge::renderer::system_ptr                       renderer_system;
	sge::renderer::device_ptr                       renderer;

	plugin::object<input::system>::ptr_type         input_plugin;
	input::system_ptr                               input_system;

	typedef fcppt::scoped_ptr<
		sge::image::multi_loader
	> image_multi_loader_ptr;

	image_multi_loader_ptr                          image_multi_loader;

	typedef fcppt::scoped_ptr<
		sge::audio::multi_loader
	> audio_multi_loader_ptr;

	audio_multi_loader_ptr                          audio_multi_loader;

	plugin::object<audio::player>::ptr_type         audio_player_plugin;
	audio::player_ptr                               audio_player;

	plugin::object<collision::system>::ptr_type     collision_plugin;
	collision::system_ptr                           collision_system;

	plugin::object<font::system>::ptr_type          font_plugin;
	font::system_ptr                                font_system;

	window::instance_ptr                            window_;

	fcppt::optional<window::parameters>             wparam_;

	void
	init_renderer(
		renderer::parameters const &
	);

	void
	init_window(
		window::parameters const &
	);

	void
	init_input();

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
		new impl()
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
	list const &l
)
{
	BOOST_FOREACH(
		any const &any_,
		l.get()
	)
		fcppt::variant::apply_unary(
			visitor(
				*impl_
			),
			any_
		);
	
	impl_->post_init();
}

sge::plugin::manager &
sge::systems::instance::plugin_manager()
{
	return impl_->plugin_manager;
}

sge::renderer::system_ptr const
sge::systems::instance::renderer_system() const
{
	return impl_->renderer_system;
}

sge::renderer::device_ptr const
sge::systems::instance::renderer() const
{
	return impl_->renderer;
}

sge::input::system_ptr const
sge::systems::instance::input_system() const
{
	return impl_->input_system;
}

sge::image::multi_loader &
sge::systems::instance::image_loader() const
{
	return *impl_->image_multi_loader;
}

sge::audio::multi_loader &
sge::systems::instance::audio_loader() const
{
	return *impl_->audio_multi_loader;
}

sge::audio::player_ptr const
sge::systems::instance::audio_player() const
{
	return impl_->audio_player;
}

sge::collision::system_ptr const
sge::systems::instance::collision_system() const
{
	return impl_->collision_system;
}

sge::font::system_ptr const
sge::systems::instance::font_system() const
{
	return impl_->font_system;
}

sge::window::instance_ptr const
sge::systems::instance::window() const
{
	return impl_->window_;
}

namespace
{

visitor::visitor(
	sge::systems::instance::impl &impl_
)
:
	impl_(impl_)
{}


void
visitor::operator()(
	sge::renderer::parameters const &p
) const
{
	impl_.init_renderer(
		p
	);
}

void
visitor::operator()(
	sge::window::parameters const &p
) const
{
	impl_.init_window(
		p
	);
}

void
visitor::operator()(
	sge::systems::image_loader const &p
) const
{
	impl_.init_image(
		p
	);
}

void
visitor::operator()(
	sge::systems::audio_loader const &p
) const
{
	impl_.init_audio_loader(
		p
	);
}

void
visitor::operator()(
	sge::systems::audio_player const &p
) const
{
	impl_.init_audio_player(
		p
	);
}

void
visitor::operator()(
	sge::systems::parameterless::type const type_
) const
{
	switch(
		type_
	)
	{
	case sge::systems::parameterless::input:
		impl_.init_input();
		return;
	case sge::systems::parameterless::collision_system:
		impl_.init_collision_system();
		return;
	case sge::systems::parameterless::font:
		impl_.init_font();
		return;
	}

	throw sge::exception(
		FCPPT_TEXT("Invalid systems::parameterless!")
	);
}

}

void
sge::systems::instance::impl::init_window(
	window::parameters const &p
)
{
	wparam_ = p;
}

void
sge::systems::instance::impl::init_renderer(
	renderer::parameters const &p
)
{
	renderer_plugin = default_plugin<renderer::system>();
	renderer_system.reset(renderer_plugin->get()());

	if(!window_)
	{
		if(!wparam_)
			throw exception(
				FCPPT_TEXT("systems: renderer device requested, but no window parameter given!")
			);

		if(!wparam_->dim())
			wparam_->dim(
				p.display_mode().size()
			);

		window_ =
			renderer_system->create_window(
				*wparam_,
				p
			);
	}

	renderer = renderer_system->create_renderer(
		p,
		static_cast<renderer::adapter_type>(0),
		window_
	);
}

void
sge::systems::instance::impl::init_input()
{
	if(!window_)
	{
		if(!wparam_)
			throw exception(
				FCPPT_TEXT("systems: input system requested, but no window parameter given!")
			);

		create_window();
	}

	input_plugin = default_plugin<sge::input::system>();

	input_system.reset(input_plugin->get()(window_));
}

void
sge::systems::instance::impl::init_collision_system()
{
	collision_plugin = default_plugin<sge::collision::system>();

	collision_system.reset(collision_plugin->get()());
}

void
sge::systems::instance::impl::init_image(
	sge::systems::image_loader const &params
)
{
	image_multi_loader.reset(
		new sge::image::multi_loader(
			plugin_manager,
			params.extensions(),
			params.capabilities()
		)
	);
}

void
sge::systems::instance::impl::init_audio_loader(
	sge::systems::audio_loader const &params
)
{
	audio_multi_loader.reset(
		new sge::audio::multi_loader(
			plugin_manager,
			params.extensions(),
			params.capabilities()
		)
	);
}

void
sge::systems::instance::impl::init_audio_player(
	sge::systems::audio_player const &param
)
{
	for(
		plugin::iterator<sge::audio::player> it(
			plugin_manager.begin<sge::audio::player>()
		);
		it != plugin_manager.end<sge::audio::player>();
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
			player->capabilities() == param.capabilities()
		)
		{
			audio_player_plugin = plugin;
			
			audio_player.reset(
				audio_player_plugin->get()()
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

	audio_player_plugin = default_plugin<sge::audio::player>();

	audio_player.reset(
		audio_player_plugin->get()()
	);
}

void
sge::systems::instance::impl::init_font()
{
	font_plugin = default_plugin<sge::font::system>();

	font_system.reset(font_plugin->get()());
}

void
sge::systems::instance::impl::post_init()
{
	if(
		wparam_ && !window_
	)
		create_window();
			
}

void
sge::systems::instance::impl::create_window()
{
	window_ = sge::window::create(
		*wparam_
	);
}

template<
	typename T
>
typename sge::plugin::object<T>::ptr_type const
sge::systems::instance::impl::default_plugin()
{
	return plugin_manager.plugin<T>().load();
}
