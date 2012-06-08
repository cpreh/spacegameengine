/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PLUGIN_MANAGER_HPP_INCLUDED
#define SGE_PLUGIN_MANAGER_HPP_INCLUDED

#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/category_array.hpp>
#include <sge/plugin/collection_fwd.hpp>
#include <sge/plugin/context_base_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/plugin/optional_cache_ref_fwd.hpp>
#include <sge/plugin/symbol.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	SGE_PLUGIN_SYMBOL
	manager(
		boost::filesystem::path const &,
		sge::plugin::optional_cache_ref const &
	);

	SGE_PLUGIN_SYMBOL
	~manager();

	template<
		typename Type
	>
	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	sge::plugin::collection<
		Type
	> const
	collection();
private:
	typedef boost::ptr_vector<
		sge::plugin::context_base
	> context_base_vector;

	typedef std::map<
		sge::plugin::capabilities::type,
		sge::plugin::category_array
	> plugin_map;

	context_base_vector plugins_;

	plugin_map categories_;
};

}
}

#endif
