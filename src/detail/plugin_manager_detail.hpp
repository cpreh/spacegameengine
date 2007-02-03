/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


namespace sge
{
namespace detail {

template<typename T> struct no_window_plugin {
	typedef T* (*plugin_function)();
	enum { needs_window = false };
};
template<typename T> struct window_plugin {
	typedef T* (*plugin_function)(window_ptr);
	enum { needs_window = true };
};

template<typename T> struct plugin_traits;
template<> struct plugin_traits<renderer_system> : no_window_plugin<renderer_system> { 
	static const char* plugin_loader_name() { return "create_renderer_system"; }
	static plugin_type get_plugin_type() { return PT_Renderer; }
};
template<> struct plugin_traits<input_system> : window_plugin<input_system> {
	static const char* plugin_loader_name() { return "create_input_system"; }
	static plugin_type get_plugin_type() { return PT_Input; }
};
template<> struct plugin_traits<image_loader> : no_window_plugin<image_loader> {
	static const char* plugin_loader_name() { return "create_image_loader"; }
	static plugin_type get_plugin_type() { return PT_ImageLoader; }
};
template<> struct plugin_traits<audio_system> : window_plugin<audio_system> {
	static const char* plugin_loader_name() { return "create_audio_system"; }
	static plugin_type get_plugin_type() { return PT_Audio; }
};
template<> struct plugin_traits<font_system> : no_window_plugin<font_system> {
	static const char* plugin_loader_name() { return "create_font_system"; }
	static plugin_type get_plugin_type() { return PT_Font; }
};

struct plugin {
	typedef shared_ptr<library> library_ptr;

	plugin(library_ptr lib, plugin_type type)
	 : lib(lib), type(type)
	{}

	library_ptr lib;
	plugin_type type;
};

struct plugin_has_flag : public std::binary_function<plugin,plugin_type,bool> {
	result_type operator()(const first_argument_type& p, const second_argument_type& t) const
	{
		return p.type&t;
	}
};

}
}
