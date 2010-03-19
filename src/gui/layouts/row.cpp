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


#include <sge/gui/layouts/row.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/log.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("layouts: row")
	)
);

}

sge::gui::layouts::row::row(
	spacing const &_spacing)
:
	base(),
	sizes(),
	spacing_(_spacing)
{
}

void sge::gui::layouts::row::compile_static()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("In static compilation for widget ")
			<< fcppt::type_name(typeid(connected_widget()))
	);

	reset_cache();

	// Make everything dirty. There's no better place to do it. If a child of
	// connected_widget() is deleted, this function gets called and we have to
	// redraw everything, else we get errors
	connected_widget().parent_manager().dirty(
		connected_widget(),
		rect(
			rect::vector::null(),
			connected_widget().size()
		)
	);

	dim const
		optimal = optimal_size(),
		usable = connected_widget().size();

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("optimal size ") << optimal
		        << FCPPT_TEXT(", usable size: ") << usable);

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting master axis begin"));
	adapt_outer(
		optimal,
		usable,
		master(
			dim(0,1)));
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting master axis end"));
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting slave axis begin"));
	adapt_outer(
		optimal,
		usable,
		slave(
			dim(0,1)));
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("adapting slave axis end"));

	// finally, set positions and sizes
	update_widgets(usable);
}

sge::gui::dim const sge::gui::layouts::row::optimal_size() const
{
	dim hint = dim::null();
	BOOST_FOREACH(widgets::base const &w,connected_widget().children())
	{
		master(hint) += master(w.optimal_size());
		slave(hint) = std::max(slave(hint),slave(w.optimal_size()));
	}
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("returning optimal size ")
		        << hint);

	return
		fcppt::math::vector::structure_cast<dim>(
			fcppt::math::dim::structure_cast<spacing>(hint) *
			spacing_
		);
}

sge::gui::dim::reference sge::gui::layouts::row::slave(
	dim &d) const
{
	if (master(d) == d.w())
		return d.h();
	return d.w();
}

sge::gui::dim::const_reference sge::gui::layouts::row::slave(
	dim const &d) const
{
	if (master(d) == d.w())
		return d.h();
	return d.w();
}

sge::gui::point::reference sge::gui::layouts::row::slave(
	point &d) const
{
	if (master(d) == d.x())
		return d.y();
	return d.x();
}

sge::gui::point::const_reference sge::gui::layouts::row::slave(
	point const &d) const
{
	if (master(d) == d.x())
		return d.y();
	return d.x();
}

void sge::gui::layouts::row::adapt(
	dim const &optimal,
	dim const &usable,
	axis_policy::type const flag,
	dim::size_type const axis)
{
	unsigned const count = count_flags(flag,axis);

	FCPPT_ASSERT_MESSAGE(
		count,
		FCPPT_TEXT("adapt called when there are no widgets to adapt"));

	unit const diff = usable[axis] - optimal[axis];
	unit const addition = static_cast<unit>(diff/count);

	FCPPT_LOG_DEBUG(mylogger,
		fcppt::log::_ << FCPPT_TEXT("adding ") << diff << FCPPT_TEXT("/")
		        << count << FCPPT_TEXT("=") << addition
						<< FCPPT_TEXT(" pixels to each widget"));

	BOOST_FOREACH(widget_map::value_type &p,sizes)
		if (p.first->size_policy().index(axis) & flag)
			p.second[axis] += addition;
}

void sge::gui::layouts::row::adapt_outer(
	dim const &optimal,
	dim const &usable,
	dim::size_type const axis)
{
	// optimal > size
	// count widgets with shrink flag and distribute (optimal - size) among
	// them. if there are no shrinkable widgets, issue an error
	// optimal < size
	// count widgets with expand flag and distribute (size - optimal) among
	// them. if there are no widgets with the expand flag, distribute space among
	// widgets with grow flag.

	if (optimal[axis] > usable[axis])
	{
		FCPPT_ASSERT_MESSAGE(
			count_flags(axis_policy::can_shrink,axis),
			FCPPT_TEXT("not enough space to hold all widgets and no shrinkable widgets found"));

		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("there is too less space, shrinking begin"));
		adapt(optimal,usable,axis_policy::can_shrink,axis);
		FCPPT_LOG_DEBUG(mylogger,fcppt::log::_ << FCPPT_TEXT("shrinking end"));
	}
	else if (optimal[axis] <= usable[axis])
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
}

void sge::gui::layouts::row::update_widgets(dim const &usable)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("update widgets begin"));

	// calculate "bounding line" of all widgets on the master axis
	unit bounding = static_cast<unit>(0);
	BOOST_FOREACH(widget_map::value_type &p,sizes)
		bounding += master(p.second);

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("bounding size in master direction is ")
		        << bounding);

	unit const extra_space = static_cast<unit>(master(usable)-bounding);
	unit const increment = static_cast<unit>(extra_space/(sizes.size()+1));

	FCPPT_LOG_DEBUG(mylogger,
		fcppt::log::_ << FCPPT_TEXT("there are ") << extra_space
		        << FCPPT_TEXT(" pixels extra space and ")
		        << increment << FCPPT_TEXT(" is the increment"));

	point pos;
	master(pos) = increment;

	BOOST_FOREACH(widget_map::value_type &p,sizes)
	{
		slave(pos) =
			static_cast<unit>(
				slave(usable)/2-slave(p.second)/2);

		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("setting widgets::base (master) position to ")
							<< master(pos)
							<< FCPPT_TEXT(" and size to ")
							<< p.second);

		base::set_widget_size(
			*p.first,
			p.second);
		base::set_widget_pos(
			*p.first,
			pos);
		base::compile_widget(
			*p.first,
			invalidation::size);

		master(pos) += master(p.second)+increment;
	}
	FCPPT_LOG_DEBUG(mylogger,fcppt::log::_ << FCPPT_TEXT("update widgets end"));
}

void sge::gui::layouts::row::reset_cache()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("resetting cache begin"));
	sizes.clear();
	BOOST_FOREACH(widgets::base &w,connected_widget().children())
	{
		dim const _optimal_size = w.optimal_size();
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("optimal size for this child is ") << _optimal_size);
		sizes.push_back(
			widget_map::value_type(
				&w,
				_optimal_size));
	}
	FCPPT_LOG_DEBUG(mylogger,fcppt::log::_ << FCPPT_TEXT("resetting cache end"));
}


unsigned sge::gui::layouts::row::count_flags(
	axis_policy::type const flags,
	dim::size_type const axis) const
{
	unsigned count = static_cast<unsigned>(0);
	BOOST_FOREACH(widgets::base const &w,connected_widget().children())
		if (w.size_policy().index(axis) & flags)
			++count;
	return count;
}
