/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED

#include <sge/gui/detail/grid_cache.hpp>
#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/axis_type.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL grid : public base
{
public:
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL dim const optimal_size() const;
private:
	typedef fcppt::scoped_ptr<detail::grid_cache> cache_ptr;
	mutable cache_ptr cache_;

	detail::grid_cache &valid_cache() const;

	void adapt_outer(
		dim const &,
		dim const &,
		axis_type);
	void shrink(
		dim const &,
		dim const &,
		axis_type);
	void expand(
		dim const &,
		dim const &,
		axis_type);
	void adapt(
		dim const &,
		dim const &,
		axis_policy::type,
		axis_type);
	void update_rolumn(
		axis_type,
		unsigned,
		axis_policy::type,
		unit);
	unsigned count_flags(
		axis_policy::type,
		axis_type) const;
	void update_cache();
	void update_policy_cache();
	void update_size_cache();
	void update_rolumn_cache();
	void distribute_overhead(
		dim const &);
	void update_widgets();
	void update_widget(
		widgets::base &,
		point const &,
		dim const &);
};
}
}
}

#endif
