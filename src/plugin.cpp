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


#include <sge/plugin.hpp>
#include <sge/audio/loader/audio_loader.hpp>
#include <sge/audio/player/audio_player.hpp>
#include <sge/font/font_system.hpp>
#include <sge/image/image_loader.hpp>
#include <sge/input/input_system.hpp>
#include <sge/renderer/renderer_system.hpp>

sge::plugin_info::plugin_info()
 : name(0),
   description(0),
   plugin_version(0),
   min_core_version(0),
   type(plugin_type::nothing)
{}

template<typename T>
sge::plugin<T>::plugin(const path& p)
: lib(p),
  loader(lib.load_function<loader_fun>(detail::plugin_traits<T>::plugin_loader_name()))
{}

template<typename T>
typename sge::plugin<T>::loader_fun sge::plugin<T>::get() const
{
	return loader;
}

template class sge::plugin<sge::audio_loader>;
template class sge::plugin<sge::audio_player>;
template class sge::plugin<sge::font_system>;
template class sge::plugin<sge::image_loader>;
template class sge::plugin<sge::input_system>;
template class sge::plugin<sge::renderer_system>;
