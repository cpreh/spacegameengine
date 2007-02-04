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


template<typename T>
typename boost::enable_if_c<sge::detail::plugin_traits<T>::needs_window == false, sge::shared_ptr<T> >::type sge::plugin_manager::get_plugin(const unsigned index)
{
	typedef typename detail::plugin_traits<T>::plugin_function plugin_function;
	return shared_ptr<T>(_get_plugin<T,plugin_function>(index)());
}

template<typename T>
typename boost::enable_if_c<sge::detail::plugin_traits<T>::needs_window == true, sge::shared_ptr<T> >::type sge::plugin_manager::get_plugin(const window_ptr w, const unsigned index)
{
	typedef typename detail::plugin_traits<T>::plugin_function plugin_function;
	return shared_ptr<T>(_get_plugin<T,plugin_function>(index)(w));
}

template<typename T, typename Fun> Fun sge::plugin_manager::_get_plugin(const unsigned index)
{
	const plugin_type type = detail::plugin_traits<T>::get_plugin_type();
	library_array::iterator it = find_nth_if(loaded_plugins.begin(),loaded_plugins.end(),index,std::bind2nd(detail::plugin_has_flag(),type));
	if(it == loaded_plugins.end())
	{
		load_plugin(type);
		it = --loaded_plugins.end();
	}
	return it->lib->load_function<Fun>(detail::plugin_traits<T>::plugin_loader_name());
}
