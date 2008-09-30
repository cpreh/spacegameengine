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


#ifndef SGE_SYSTEMS_INSTANCE_HPP_INCLUDED
#define SGE_SYSTEMS_INSTANCE_HPP_INCLUDED

#include "../plugin/manager.hpp"
#include "../plugin/plugin.hpp"
#include "../renderer/device_fwd.hpp"
#include "../renderer/system_fwd.hpp"
#include "../font/system_fwd.hpp"
#include "../input/system_fwd.hpp"
#include "../image/loader_fwd.hpp"
#include "../audio/player_fwd.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace systems
{

class list;

struct instance : boost::noncopyable {
	SGE_SYMBOL explicit instance(
		list const &);

	plugin::manager &plugin_manager();

	renderer::system_ptr const renderer_system() const;
	renderer::device_ptr const renderer_device() const;

	input::system_ptr const input_system() const;

	image::loader_ptr const image_loader() const; // TODO: replace this with an image prober

	audio::player_ptr const audio_player() const;

	font::system_ptr const font_system() const;
private:
	plugin::manager                            plugin_manager_;

	plugin::plugin<renderer::system>::ptr_type renderer_plugin;
	renderer::system_ptr                       renderer_system_;
	renderer::device_ptr                       renderer_device_;

	plugin::plugin<input::system>::ptr_type    input_plugin;
	input::system_ptr                          input_system;

	plugin::plugin<image::loader>::ptr_type    image_loader_plugin;
	image::loader_ptr                          image_loader_;

	plugin::plugin<audio::player>::ptr_type    audio_player_plugin;
	audio::player_ptr                          audio_player;

	plugin::plugin<font::system>::ptr_type     font_plugin;
	font::system_ptr                           font_system;
};

}

#endif
