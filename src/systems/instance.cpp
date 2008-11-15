/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/plugin/plugin.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/device.hpp>
#include <sge/input/system.hpp>
#include <sge/image/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/font/system.hpp>
#include <sge/window/instance.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/foreach.hpp>

struct sge::systems::instance::impl {
	plugin::manager                            plugin_manager;

	plugin::plugin<renderer::system>::ptr_type renderer_plugin;
	renderer::system_ptr                       renderer_system;
	renderer::device_ptr                       renderer;

	plugin::plugin<input::system>::ptr_type    input_plugin;
	input::system_ptr                          input_system;

	plugin::plugin<image::loader>::ptr_type    image_loader_plugin;
	image::loader_ptr                          image_loader;

	plugin::plugin<audio::player>::ptr_type    audio_player_plugin;
	audio::player_ptr                          audio_player;

	plugin::plugin<font::system>::ptr_type     font_plugin;
	font::system_ptr                           font_system;
	
	window::instance_ptr                       window_;

	void init_renderer(
		renderer::parameters const &);
	void init_input();
	void init_image();
	void init_audio_player();
	void init_font();
};

namespace
{

struct visitor : boost::static_visitor<> {
	explicit visitor(
		sge::systems::instance::impl &);
	
	void operator()(
		sge::renderer::parameters const &) const;
	void operator()(
		sge::systems::parameterless::type) const;
private:
	sge::systems::instance::impl &impl_;
};

}

sge::systems::instance::instance(
	list const &l)
:
	impl_(
		new impl())
{
	reinit(l);
}

sge::systems::instance::~instance()
{}

void sge::systems::instance::reinit(
	list const &l)
{
	visitor v(*impl_);
	BOOST_FOREACH(any const &a, l.get())
		boost::apply_visitor(
			v,
			a);
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

sge::image::loader_ptr const
sge::systems::instance::image_loader() const
{
	return impl_->image_loader;
}

sge::audio::player_ptr const
sge::systems::instance::audio_player() const
{
	return impl_->audio_player;
}

sge::font::system_ptr const
sge::systems::instance::font_system() const
{
	return impl_->font_system;
}

namespace
{

visitor::visitor(
	sge::systems::instance::impl &impl_)
:
	impl_(impl_)
{}

void visitor::operator()(
	sge::renderer::parameters const &p) const
{
	impl_.init_renderer(p);
}

void visitor::operator()(
	sge::systems::parameterless::type const p) const
{
	switch(p) {
	case sge::systems::parameterless::input:
		impl_.init_input();
		break;
	case sge::systems::parameterless::image:
		impl_.init_image();
		break;
	case sge::systems::parameterless::audio_player:
		impl_.init_audio_player();
		break;
	case sge::systems::parameterless::font:
		impl_.init_font();
		break;
	default:
		throw sge::exception(
			SGE_TEXT("Invalid systems::parameterless!"));
	}
}

}

void sge::systems::instance::impl::init_renderer(
	renderer::parameters const &p)
{
	renderer_plugin = plugin_manager.get_plugin<renderer::system>().load();
	renderer_system.reset(renderer_plugin->get()());

	if(!window_)
		window_ = renderer_system->create_window(
			p);
	
	renderer = renderer_system->create_renderer(
		p,
		static_cast<renderer::adapter_type>(0),
		window_);
}

void sge::systems::instance::impl::init_input()
{
	// TODO: create a window here too if not done already, using sge::create_window
	input_plugin = plugin_manager.get_plugin<sge::input::system>().load();
	input_system.reset(input_plugin->get()(renderer->window()));
}

void sge::systems::instance::impl::init_image()
{
	image_loader_plugin = plugin_manager.get_plugin<sge::image::loader>().load();
	image_loader.reset(image_loader_plugin->get()());
}

void sge::systems::instance::impl::init_audio_player()
{
	audio_player_plugin = plugin_manager.get_plugin<sge::audio::player>().load();
	audio_player.reset(audio_player_plugin->get()());
}

void sge::systems::instance::impl::init_font()
{
	font_plugin = plugin_manager.get_plugin<sge::font::system>().load();
	font_system.reset(font_plugin->get()());
}
