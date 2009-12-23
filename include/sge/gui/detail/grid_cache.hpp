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


#ifndef SGE_GUI_DETAIL_GRID_CACHE_HPP_INCLUDED
#define SGE_GUI_DETAIL_GRID_CACHE_HPP_INCLUDED

#include <sge/gui/dim.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/size_policy.hpp>
#include <fcppt/container/field.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <vector>
#include <map>

namespace sge
{
namespace gui
{
namespace detail
{
class grid_cache
{
public:
	class widget_data
	{
	public:
		/*dim optimal_size;
		dim final_size;
    */
		dim size;

		widget_data();
	};

	class rolumn_data
	{
	public:
		unit size;
		axis_policy::type policy;

		rolumn_data();
	};

	// the "real" grid
	typedef fcppt::container::field<
		fcppt::container::raw_vector<
			widgets::base *
		>
	> child_plane;
	typedef child_plane::size_type size_type;
	// stores the size data for each widget (is there because the real grid could
	// be sparse
	typedef std::map<
		widgets::base*,
		widget_data
	> data_map;
	// stores data per column and row (per rolumn)
	typedef fcppt::container::field<
		std::vector<
			rolumn_data
		>
	> rolumn_container;

	grid_cache(
		widgets::base::child_container const &);

	child_plane &plane();
	data_map &data();
	rolumn_container &rolumns();
	rolumn_container &volatile_rolumns();
private:
	widgets::base::child_container const &widgets_;

	child_plane      plane_;
	data_map         data_;
	rolumn_container rolumns_;
	rolumn_container volatile_rolumns_;

	void first_pass();
	void second_pass();
};
}
}
}

#endif
