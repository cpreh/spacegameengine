#include <sge/gui/layouts/row.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/log.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include "../utility/bitfield_and.hpp"

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("layouts: row"),
	true);
}

sge::gui::layouts::row::row()
: 
	base()
{
}

void sge::gui::layouts::row::compile()
{
	if (!connected_widget().has_parent())
		base::set_widget_size(
			connected_widget(),
			connected_widget().size_hint());
		
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("updating"));

	reset_cache();
	dim const 
		optimal = size_hint(),
		usable = connected_widget().size();
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("optimal size ") << optimal 
		        << SGE_TEXT(", usable size: ") << usable);

	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting master axis begin"));
	adapt_outer(
		optimal,
		usable,
		master(
			dim(0,1)));
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting master axis end"));
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting slave axis begin"));
	adapt_outer(
		optimal,
		usable,
		slave(
			dim(0,1)));
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting slave axis end"));

	// finally, set positions and sizes
	update_widgets(usable);
}

sge::gui::dim const sge::gui::layouts::row::size_hint() const
{
	dim hint = dim::null();
	BOOST_FOREACH(widgets::base const &w,connected_widget().children())
	{
		master(hint) += master(w.size_hint());
		slave(hint) = std::max(slave(hint),slave(w.size_hint()));
	}
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("returning size hint") 
		        << hint);
	return hint;
}

sge::gui::dim::reference sge::gui::layouts::row::slave(dim &d) const
{
	if (master(d) == d.w())
		return d.h();
	return d.w();
}

sge::gui::dim::const_reference sge::gui::layouts::row::slave(dim const &d) const
{
	if (master(d) == d.w())
		return d.h();
	return d.w();
}

sge::gui::point::reference sge::gui::layouts::row::slave(point &d) const
{
	if (master(d) == d.x())
		return d.y();
	return d.x();
}

sge::gui::point::const_reference sge::gui::layouts::row::slave(point const &d) const
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

	SGE_ASSERT_MESSAGE(
		count,
		SGE_TEXT("adapt called when there are no widgets to adapt"));

	unit const diff = usable[axis] - optimal[axis];
	unit const addition = static_cast<unit>(diff/count);

	SGE_LOG_DEBUG(mylogger,
		log::_1 << SGE_TEXT("adding ") << diff << SGE_TEXT("/") 
		        << count << SGE_TEXT("=") << addition 
						<< SGE_TEXT(" pixels to each widget"));

	BOOST_FOREACH(widget_map::value_type &p,sizes)
		if (utility::bitfield_and(p.first->size_policy().index(axis),flag))
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
		SGE_ASSERT_MESSAGE(
			count_flags(axis_policy::can_shrink,axis),
			SGE_TEXT("not enough space to hold all widgets and no shrinkable widgets found"));

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("there is too less space, shrinking begin"));
		adapt(optimal,usable,axis_policy::can_shrink,axis);
		SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("shrinking end"));
	}
	else
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("there is too much space, expanding begin"));
		unsigned count;
		if ((count = count_flags(axis_policy::should_grow,axis)))
		{
			SGE_LOG_DEBUG(mylogger,
				log::_1 << SGE_TEXT("there are ") << count 
				        << SGE_TEXT(" widgets which should grow, growing those"));
			adapt(optimal,usable,axis_policy::should_grow,axis);
		}
		else if ((count = count_flags(axis_policy::can_grow,axis)))
		{
			SGE_LOG_DEBUG(mylogger,
				log::_1 << SGE_TEXT("there are ") << count 
				        << SGE_TEXT(" widgets which can grow, growing those"));
			adapt(optimal,usable,axis_policy::can_grow,axis);
		}
		else
		{
			SGE_LOG_DEBUG(mylogger,
				log::_1 << SGE_TEXT("there are widgets no widgets which could grow :("));
		}
		SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("expanding end"));
	}
}

void sge::gui::layouts::row::update_widgets(dim const &usable)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("update widgets begin"));

	// calculate "bounding line" of all widgets on the master axis
	unit bounding = static_cast<unit>(0);
	BOOST_FOREACH(widget_map::value_type &p,sizes)
		bounding += master(p.second);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("bounding size in master direction is ")
		        << bounding);
	
	unit const extra_space = static_cast<unit>(master(usable)-bounding);
	unit const increment = static_cast<unit>(extra_space/(sizes.size()+1));
	
	SGE_LOG_DEBUG(mylogger,
		log::_1 << SGE_TEXT("there are ") << extra_space 
		        << SGE_TEXT(" pixels extra space and ") 
		        << increment << SGE_TEXT(" is the increment"));

	point pos;
	master(pos) = increment;

	BOOST_FOREACH(widget_map::value_type &p,sizes)
	{
		slave(pos) =
			static_cast<unit>(
				slave(usable)/2-slave(p.second)/2);

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("setting widgets::base (master) position to ")
							<< master(pos)
							<< SGE_TEXT(" and size to ")
							<< p.second);
		
		base::set_widget_size(*p.first,p.second);
		base::set_widget_pos(*p.first,pos);
		base::compile_widget(*p.first);

		master(pos) += master(p.second)+increment;
	}
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("update widgets end"));
}

void sge::gui::layouts::row::reset_cache()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resetting cache begin"));
	sizes.clear();
	BOOST_FOREACH(widgets::base &w,connected_widget().children())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("size hint for this child is ") << w.size_hint());
		sizes.push_back(widget_map::value_type(&w,w.size_hint()));
	}
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("resetting cache end"));
}


unsigned sge::gui::layouts::row::count_flags(
	axis_policy::type const flags,
	dim::size_type const axis) const
{
	unsigned count = static_cast<unsigned>(0);
	BOOST_FOREACH(widgets::base const &w,connected_widget().children())
		//if (utility::bitfield_and(w.size_policy().index(axis),flags))
		if (w.size_policy().index(axis) & flags)
			++count;
	return count;
}
