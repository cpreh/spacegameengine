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


#ifndef SGE_PLUGIN_MANAGER_HPP_INCLUDED
#define SGE_PLUGIN_MANAGER_HPP_INCLUDED

#include <string>
#include <list>
#include <functional>
#include <boost/filesystem/path.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include "algorithm.hpp"
#include "library.hpp"
#include "window.hpp"
#include "plugin.hpp"
#include "renderer/renderer_system.hpp"
#include "input/input_system.hpp"
#include "image/image_loader.hpp"
#include "audio/audio_system.hpp"
#include "font/font_system.hpp"
#include "detail/plugin_manager_detail.hpp"

namespace sge
{

class plugin_manager {
public:
	typedef std::vector<plugin_info> plugin_info_array;

	plugin_manager();
	void load_plugin(plugin_type mask, unsigned number = 0);
	void load_plugin(const std::string& filename);
	void get_plugin_info(plugin_type mask, plugin_info_array& v);
	template<typename T> 
		typename boost::enable_if<detail::plugin_traits<T>, shared_ptr<T> >::type get_plugin(const unsigned index = 0);
	template<typename T> 
		typename boost::enable_if<detail::plugin_traits<T>, shared_ptr<T> >::type get_plugin(const window_ptr w, const unsigned index = 0);
private:
	template<typename T, typename Fun> Fun _get_plugin(const unsigned index);

	plugin_info_array plugin_infos;
	typedef std::list<detail::plugin> library_array;
	library_array loaded_plugins;
	boost::filesystem::path mypath;
};

}

#include "./detail/plugin_manager_impl.hpp"

#endif
