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

#include <cstddef>
#include <vector>
#include <map>
#include <iterator>
#include <boost/noncopyable.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include "shared_ptr.hpp"
#include "plugin.hpp"
#include "string.hpp"
#include "exception.hpp"

namespace sge
{

class plugin_manager : boost::noncopyable {
public:
	template<typename T> class plugin_context;

	class plugin_context_base {
	public:
		plugin_context_base(const std::string& path);

		const std::string& name() const;
		const std::string& description() const;
		unsigned version() const;
		plugin_type type() const;
		const std::string& path() const;
	private:
		template<typename T> friend class plugin_context;
		boost::weak_ptr<plugin_base> ref;
		std::string _path;
		std::string _name;
		std::string _description;
		unsigned _version;
		plugin_type _type;
	};

	template<typename T>
	class plugin_context {
	public:
		plugin_context(plugin_context_base& base_)
		: base(&base_)
		{}

		typedef shared_ptr<plugin<T> > ptr_type;

		ptr_type load()
		{
			const shared_ptr<plugin_base> ptr_base(base->ref.lock());
			if(!ptr_base)
			{
				const shared_ptr<plugin<T> > new_ptr(new plugin<T>(base->path()));
				base->ref = new_ptr.get_boost_ptr();
				return new_ptr;
			}
			return polymorphic_pointer_cast<plugin<T> >(ptr_base);
		}
	private:
		plugin_context_base* base;
	};

private:
	typedef std::vector<plugin_context_base> plugin_array;
	typedef std::vector<plugin_context_base*> plugin_category_array;
	typedef std::map<plugin_type, plugin_category_array> plugin_map;
public:
	typedef std::size_t size_type;

	plugin_manager();

	template<typename T>
		class iterator : public boost::iterator_facade<iterator<T>, plugin_context<T>, std::random_access_iterator_tag, plugin_context<T> > {
	public:
		typedef boost::iterator_facade<iterator<T>, plugin_context<T>, std::random_access_iterator_tag, plugin_context<T> > base_type;

		typedef typename base_type::value_type value_type;
		typedef typename base_type::reference reference;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::difference_type difference_type;

		iterator(const plugin_category_array::iterator it)
		: it(it)
		{}

		void advance(const difference_type diff)
		{
			it+=diff;
		}

		void increment()
		{
			++it;
		}

		void decrement()
		{
			--it;
		}

		bool equal(const iterator& r) const
		{
			return it == r.it;
		}

		reference dereference() const
		{
			return plugin_context<T>(**it);
		}

		difference_type distance_to(const iterator& r) const
		{
			return r.it - it;
		}
	private:
		plugin_category_array::iterator it;
	};

	template<typename T>
		iterator<T> begin()
	{
		return iterator<T>(categories[detail::plugin_traits<T>::get_plugin_type()].begin());
	}

	template<typename T>
		iterator<T> end()
	{
		return iterator<T>(categories[detail::plugin_traits<T>::get_plugin_type()].end());
	}

	template<typename T>
		typename iterator<T>::reference get_plugin(const size_type index = 0)
	{
		if(index >= size<T>())
			throw exception("get_plugin(): No plugins found of type: \"" + std::string(typeid(T).name()) + "\"!");
		return *(begin<T>()+index);
	}

	template<typename T>
		size_type size() const
	{
		const plugin_map::const_iterator it = categories.find(detail::plugin_traits<T>::get_plugin_type());
		if(it == categories.end())
			return 0;
		return it->second.size();
	}
private:
	plugin_array plugins;
	plugin_map categories;
};

}

#endif
