#ifndef SGE_PLUGIN_MANAGER_HPP_INCLUDED
#define SGE_PLUGIN_MANAGER_HPP_INCLUDED

#include <string>
#include <list>
#include <functional>
#include <boost/filesystem/path.hpp>
#include "./algorithm.hpp"
#include "./library.hpp"
#include "./window.hpp"
#include "./plugin.hpp"
#include "../renderer/renderer_system.hpp"
#include "../input/input_system.hpp"
#include "../image/image_loader.hpp"
#include "../audio/audio_system.hpp"
#include "../font/font_system.hpp"

namespace sge
{
	namespace detail {
		template<typename T> struct plugin_traits;
		template<typename T> struct no_window_plugin { typedef T* (*plugin_function)(); };
		template<typename T> struct window_plugin { typedef T* (*plugin_function)(window_ptr); };
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
	}
	
	class plugin_manager {
		typedef shared_ptr<library> library_ptr;
		struct plugin {
			plugin(library_ptr lib, plugin_type type) : lib(lib), type(type) {} library_ptr lib; plugin_type type; };
		struct equal_type : public std::binary_function<plugin,plugin_type,bool> {
			result_type operator()(const first_argument_type& p, const second_argument_type& t) const { return p.type&t; } };
	public:
		typedef std::vector<plugin_info> plugin_info_array;

		SGECOREDLLAPI plugin_manager();
		SGECOREDLLAPI void load_plugin(plugin_type mask, unsigned number = 0);
		SGECOREDLLAPI void load_plugin(const std::string& filename);
		SGECOREDLLAPI void get_plugin_info(plugin_type mask, plugin_info_array& v);
		template<typename T> shared_ptr<T> get_plugin(const unsigned index = 0)
		{
			typedef typename detail::plugin_traits<T>::plugin_function plugin_function;
			return shared_ptr<T>(_get_plugin<T,plugin_function>(index)());
		}
		template<typename T> shared_ptr<T> get_plugin(const window_ptr w, const unsigned index = 0)
		{
			typedef typename detail::plugin_traits<T>::plugin_function plugin_function;
			return shared_ptr<T>(_get_plugin<T,plugin_function>(index)(w));
		}
	private:
		template<typename T, typename Fun> Fun _get_plugin(const unsigned index)
		{
			const plugin_type type = detail::plugin_traits<T>::get_plugin_type();
			library_array::iterator it = find_nth_if(loaded_plugins.begin(),loaded_plugins.end(),index,std::bind2nd(equal_type(),type));
			
			if(it == loaded_plugins.end())
			{
				load_plugin(type);
				it = --loaded_plugins.end();
			}
			return c_cast<Fun>(it->lib->get_function(detail::plugin_traits<T>::plugin_loader_name()));
		}
		
		plugin_info_array plugin_infos;
		typedef std::list<plugin> library_array;
		library_array loaded_plugins;
		boost::filesystem::path mypath;
	};
}

#endif
