/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/detail/grid_cache.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/axis_type.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/widgets/base.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/container/assign_multi_array.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("layouts: grid")
	)
);

sge::gui::axis_type
	x_axis = 0,
	y_axis = 1;
}

void sge::gui::layouts::grid::compile_static()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("In static compilation for widget ")
			<< fcppt::type_name(typeid(connected_widget()))
	);

	cache_.reset(
		new detail::grid_cache(
			connected_widget().children()));

	// Make everything dirty. There's no better place to do it. If a child of
	// connected_widget() is deleted, this function gets called and we have to
	// redraw everything, else we get errors
	connected_widget().parent_manager().dirty(
		connected_widget(),
		rect(
			point::null(),
			connected_widget().size()
		)
	);

	dim const
		optimal = optimal_size(),
		usable = connected_widget().size();

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("optimal size ") << optimal
			<< FCPPT_TEXT(", usable size: ") << usable
	);

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting y axis begin"));
	adapt_outer(
		optimal,
		usable,
		y_axis);
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting y axis end"));
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting x axis begin"));
	adapt_outer(
		optimal,
		usable,
		x_axis);
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting x axis end"));

	distribute_overhead(
		usable);
	update_widgets();
}

sge::gui::dim const sge::gui::layouts::grid::optimal_size() const
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("optimal size, begin"));

	detail::grid_cache::rolumn_container const &rolumns =
		valid_cache().rolumns();

	dim maxdims = dim::null();

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("rolumn dimension is ")
		        << rolumns.shape()[0] << FCPPT_TEXT('x') << rolumns.shape()[1]);

	for (
		detail::grid_cache::rolumn_container::size_type i = 0;
		i < rolumns.shape()[1];
		++i)
		for (
			unit j = static_cast<unit>(0);
			j < static_cast<unit>(2);
			++j)
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_
					<< FCPPT_TEXT("axis: ")
					<< j
					<< FCPPT_TEXT(", rolumn ")
					<< i
					<< FCPPT_TEXT(", adding size ")
					<< rolumns[j][i].size
			);

			maxdims[j] += rolumns[j][i].size;
		}

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("optimal size, end"));

	return maxdims;
}

sge::gui::detail::grid_cache &sge::gui::layouts::grid::valid_cache() const
{
	if (!cache_)
		cache_.reset(
			new detail::grid_cache(
				connected_widget().children()));
	return *cache_;
}

// this decides if an axis should shrink or expand due to the too big or too
// small usable size
void sge::gui::layouts::grid::adapt_outer(
	dim const &optimal,
	dim const &usable,
	axis_type const axis)
{
	// optimal > size
	// count widgets with shrink flag and distribute (optimal - size) among
	// them. if there are no shrinkable widgets, issue an error
	// optimal < size
	// count widgets with expand flag and distribute (size - optimal) among
	// them. if there are no widgets with the expand flag, distribute space among
	// widgets with grow flag.
	if (optimal[axis] > usable[axis])
		shrink(
			optimal,
			usable,
			axis);
	else
		expand(
			optimal,
			usable,
			axis);
}

void sge::gui::layouts::grid::shrink(
	dim const &optimal,
	dim const &usable,
	axis_type const axis)
{
	FCPPT_ASSERT_MESSAGE(
		count_flags(
			axis_policy::can_shrink,
			axis),
		FCPPT_TEXT("not enough space to hold all widgets and no shrinkable widgets found"));

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("there is too less space, shrinking begin"));
	adapt(
		optimal,
		usable,
		axis_policy::can_shrink,
		axis);
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("shrinking end"));
}

void sge::gui::layouts::grid::expand(
	dim const &optimal,
	dim const &usable,
	axis_type const axis)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("there is too much space, expanding begin"));

	unsigned count;
	if ((count = count_flags(axis_policy::should_grow,axis)))
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("there are ")
			<< count
			<< FCPPT_TEXT(" widgets which should grow, growing those"));

		adapt(
			optimal,
			usable,
			axis_policy::should_grow,
			axis);
	}
	else if ((count = count_flags(axis_policy::can_grow,axis)))
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("there are ")
							<< count
							<< FCPPT_TEXT(" widgets which can grow, growing those"));

		adapt(
			optimal,
			usable,
			axis_policy::can_grow,
			axis);
	}
	else
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("there are no widgets which could grow :("));
	}
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("expanding end"));
}

void sge::gui::layouts::grid::adapt(
	dim const &optimal,
	dim const &usable,
	axis_policy::type const flag,
	axis_type const axis)
{
	unsigned const count =
		count_flags(
			flag,
			axis);

	FCPPT_ASSERT_MESSAGE(
		count,
		FCPPT_TEXT("adapt called when there are no widgets to adapt"));

	// how much extra space do we have on this axis?
	unit const diff = usable[axis] - optimal[axis];
	// distribute the extra space among all flexible widgets (the assert above
	// ensures that we don't divide by zero)
	unit const addition = static_cast<unit>(diff/count);

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adding ") << diff << FCPPT_TEXT("/")
		        << count << FCPPT_TEXT("=") << addition
						<< FCPPT_TEXT(" pixels to the flagged rolumns"));

	detail::grid_cache::rolumn_container const &rolumns =
		valid_cache().rolumns();

	for (
		detail::grid_cache::child_plane::size_type i = 0;
		i < valid_cache().plane().shape()[axis];
		++i
		)
	{
		if (rolumns[axis][i].policy & flag)
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ << FCPPT_TEXT("rolumn ") << i << FCPPT_TEXT(" can be modified"));

			update_rolumn(
				axis,
				static_cast<unsigned>(i),
				flag,
				addition);
		}
	}
}

namespace
{
template<
	typename Result,
	class Container,
	typename Index>
Result field_swap_pos(
	Container &f,
	bool swap,
	Index const a,
	Index const b)
{
	return
		swap
			? f[b][a]
			: f[a][b];
}
}

void sge::gui::layouts::grid::update_rolumn(
	axis_type const axis,
	unsigned const rolumn,
	axis_policy::type const flag,
	unit const addition)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("updating rolumn ")
		        << rolumn
						<< FCPPT_TEXT(" on axis ")
						<< axis);
	// update the cache
	valid_cache().rolumns()[axis][rolumn].size += addition;

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("added addition, plane dimensions are: ")
		        << valid_cache().plane().shape()[0] << FCPPT_TEXT('x') << valid_cache().plane().shape()[1]);

	for (
		detail::grid_cache::child_plane::size_type i = 0;
		i < valid_cache().plane().shape()[1-axis];
		++i)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("swapping positions: ")
							<< bool(axis)
							<< FCPPT_TEXT(" and accessing ")
							<< i << FCPPT_TEXT("x") << rolumn);

		widgets::base * const w =
			field_swap_pos<
				widgets::base*,
				detail::grid_cache::child_plane,
				unsigned
			>(
				valid_cache().plane(),
				!static_cast<bool>(axis),
				static_cast<unsigned>(
					i),
				static_cast<unsigned>(
					rolumn));

		// not a widget we're looking for
		if (!w || !(w->size_policy().index(axis) & flag))
			continue;

		valid_cache().data()[w].size[axis] += addition;
	}
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("update rolumn, end "));
}

// counts the number of widgets on the specified axis (not rolumn, axis) which
// have the specified axis policy flag (uses the cache!)
unsigned sge::gui::layouts::grid::count_flags(
	axis_policy::type const flags,
	axis_type const axis) const
{
	unsigned count = 0;

	detail::grid_cache::rolumn_container const &rolumns =
		valid_cache().rolumns();

	for (
		detail::grid_cache::rolumn_container::size_type i = 0;
		i < rolumns.shape()[0];
		++i)
		if (rolumns[axis][i].policy & flags)
			++count;

	return count;
}

void sge::gui::layouts::grid::distribute_overhead(
	dim const &usable)
{
	detail::grid_cache::rolumn_container &rolumns =
		valid_cache().volatile_rolumns();

	// NOTE: operator= only works if the shapes match, so first reshape and resize here
	fcppt::container::assign_multi_array(
		rolumns,
		valid_cache().rolumns());

	// we might have overhead space (difference "usable - real"), which we
	// distribute evenly among rolumns
	dim real = dim::null();
	for (detail::grid_cache::rolumn_container::size_type i = 0; i < rolumns.shape()[1]; ++i)
		real += dim(
			rolumns[x_axis][i].size,
			rolumns[y_axis][i].size);

	dim const
		diff = usable - real,
		extra(
			diff.w()/
			static_cast<unit>(valid_cache().plane().shape()[0]),
			diff.h()/
			static_cast<unit>(valid_cache().plane().shape()[1]));


	for (detail::grid_cache::rolumn_container::size_type i = 0; i < rolumns.shape()[1]; ++i)
		for (detail::grid_cache::rolumn_container::size_type j = 0; j < 2; ++j)
			rolumns[j][i].size += extra[static_cast<dim::size_type>(j)];
}

// iterates through the whole table, calculating the minimal size for the
// table. if we have extra space to spare, align widgets to their alignment property
void sge::gui::layouts::grid::update_widgets()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("updating widgets begin"));

	detail::grid_cache::child_plane &c =
		valid_cache().plane();

	detail::grid_cache::rolumn_container const &rolumns =
		valid_cache().volatile_rolumns();

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("volatile rolumns dim: ")
		        << rolumns.size());

	// this pos represents the "screen position", not the position in the array
	point pos = point::null();
	for (detail::grid_cache::rolumn_container::size_type x = 0; x < c.shape()[0]; ++x)
	{
		pos.y() = static_cast<unit>(0);
		for (detail::grid_cache::rolumn_container::size_type y = 0; y < c.shape()[1]; ++y)
		{
			widgets::base * const w =
				c[x][y];
			if (w)
				update_widget(
					*w,
					pos,
					dim(
						rolumns[x_axis][x].size,
						rolumns[y_axis][y].size
					)
				);

			pos.y() +=
				rolumns[y_axis][y].size;
		}
		pos.x() +=
			rolumns[x_axis][x].size;
	}

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("updating widgets end"));
}

namespace
{
sge::gui::point const center(
	sge::gui::point const &pos,
	sge::gui::dim const &rect,
	sge::gui::dim const &smaller)
{
	return pos + (rect/static_cast<sge::gui::unit>(2)) - (smaller/static_cast<sge::gui::unit>(2));
}
}

// the widget has got it's size in data[&w].size, it just has to be aligned in
// it's cell, denoted by d.
void sge::gui::layouts::grid::update_widget(
	widgets::base &w,
	point const &p,
	dim const &d)
{
	dim const smaller =
		valid_cache().data()[&w].size;

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("setting widget position to ")
			<< p
			<< FCPPT_TEXT(", with large size ")
			<< d
			<< FCPPT_TEXT(" and small size ")
			<< smaller
			<< FCPPT_TEXT(" and centered position ")
			<< center(p,d,smaller)
	);

	base::set_widget_pos(
		w,
		center(
			p,
			d,
			smaller));

	base::set_widget_size(
		w,
		smaller);

	base::compile_widget(
		w,
		invalidation::all);
}
