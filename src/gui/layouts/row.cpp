#include <sge/gui/layouts/row.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/log.hpp>
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include "../utility/bitfield_and.hpp"

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("layouts::row"),false);
}

sge::gui::layouts::row::row(widget &w)
	: layout(w)
{
}

sge::gui::dim const sge::gui::layouts::row::size_hint() const
{
	dim hint = dim::null();
	BOOST_FOREACH(widget const &w,connected_widget().children())
	{
		hint[master()] += w.size_hint()[master()];
		hint[slave()] = std::max(hint[slave()],w.size_hint()[slave()]);
	}
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("returning size hint") 
		        << hint);
	return hint;
}

void sge::gui::layouts::row::reset_cache()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resetting cache begin"));
	sizes.clear();
	BOOST_FOREACH(widget &w,connected_widget().children())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("size hint for this child is ") << w.size_hint());
		sizes.push_back(widget_map::value_type(&w,w.size_hint()));
	}
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("resetting cache end"));
}

void sge::gui::layouts::row::adapt(
	dim const &optimal,
	dim const &usable,
	axis_policy::type const flag,
	std::size_t const axis)
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
	std::size_t const axis)
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
				        << SGE_TEXT(" widgets which can show grow, growing those"));
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
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("update widgets begin"));

	// calculate "bounding line" of all widgets on the master axis
	unit bounding = static_cast<unit>(0);
	BOOST_FOREACH(widget_map::value_type &p,sizes)
		bounding += p.second[master()];
	
	unit const extra_space = static_cast<unit>(usable[master()]-bounding);
	unit const increment = static_cast<unit>(extra_space/(sizes.size()+1));
	
	SGE_LOG_DEBUG(mylogger,
		log::_1 << SGE_TEXT("there are ") << extra_space 
		        << SGE_TEXT(" pixels extra space and ") 
		        << increment << SGE_TEXT(" is the increment"));

	point pos;
	pos[master()] = static_cast<unit>(connected_widget().pos()[master()]+increment);

	BOOST_FOREACH(widget_map::value_type &p,sizes)
	{
		pos[slave()] = 
			static_cast<unit>(
				connected_widget().pos()[slave()]+usable[slave()]/2-p.second[slave()]/2);
		
		layout::set_widget_size(*p.first,p.second);
		layout::set_widget_pos(*p.first,pos);
		layout::compile_widget(*p.first);

		pos[master()] += p.second[master()]+increment;
	}
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("update widgets end"));
}

void sge::gui::layouts::row::update()
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("updating"));

	reset_cache();
	dim const optimal = size_hint(),usable = connected_widget().size();
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("optimal size ") << optimal 
		        << SGE_TEXT(", usable size: ") << usable);

	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting master axis begin"));
	adapt_outer(optimal,usable,master());
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting master axis end"));
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting slave axis begin"));
	adapt_outer(optimal,usable,slave());
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("adapting slave axis end"));

	// finally, set positions and sizes
	update_widgets(usable);
}

void sge::gui::layouts::row::pos(point const &p)
{
	layout::set_widget_pos(connected_widget(),p);
	update();
}

void sge::gui::layouts::row::size(dim const &s)
{
	layout::set_widget_size(connected_widget(),s);
	update();
}

unsigned sge::gui::layouts::row::count_flags(
	axis_policy::type const flags,
	std::size_t const axis) const
{
	unsigned count = static_cast<unsigned>(0);
	BOOST_FOREACH(widget const &w,connected_widget().children())
		//if (utility::bitfield_and(w.size_policy().index(axis),flags))
		if (w.size_policy().index(axis) & flags)
			++count;
	return count;
}

