#include <sge/gui/log.hpp>
#include <sge/gui/axis_type.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/dim/dim.hpp>
#include <sge/math/negative.hpp>
#include <sge/type_name.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include "grid/cache.hpp"

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("layouts: grid"),
	true);

sge::gui::axis_type
	x_axis = 0,
	y_axis = 1;
}

void sge::gui::layouts::grid::compile_static()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("In static compilation for widget ")
		        << type_name(typeid(connected_widget())));
	
	cache_.reset(
		new cache(
			*this));

	// Make everything dirty. There's no better place to do it. If a child of
	// connected_widget() is deleted, this function gets called and we have to
	// redraw everything, else we get errors
	connected_widget().parent_manager().dirty(
		connected_widget(),
		rect(
			connected_widget().size()));
	
	dim const 
		optimal = optimal_size(),
		usable = connected_widget().size();

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("optimal size ") << optimal 
		        << SGE_TEXT(", usable size: ") << usable);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adapting y axis begin"));
	adapt_outer(
		optimal,
		usable,
		y_axis);
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adapting y axis end"));
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adapting x axis begin"));
	adapt_outer(
		optimal,
		usable,
		x_axis);
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adapting x axis end"));
	
	update_widgets();
}

sge::gui::dim const sge::gui::layouts::grid::optimal_size() const
{
	cache::rolumn_container const &rolumns =
		valid_cache().rolumns();

	dim maxdims = dim::null();

	for (
		cache::rolumn_container::size_type i = 0; 
		i < rolumns.dim().h();
		++i)
		for (
			unit j = static_cast<unit>(0); 
			j < static_cast<unit>(2); 
			++j)
			maxdims[j] += rolumns.pos(cache::rolumn_container::vector_type(j,i)).size;
	
	return maxdims;
}

sge::gui::layouts::grid::cache &sge::gui::layouts::grid::valid_cache() const
{
	if (!cache_)
		cache_.reset(
			new cache(*this));
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
	SGE_ASSERT_MESSAGE(
		count_flags(
			axis_policy::can_shrink,
			axis),
		SGE_TEXT("not enough space to hold all widgets and no shrinkable widgets found"));

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("there is too less space, shrinking begin"));
	adapt(
		optimal,
		usable,
		axis_policy::can_shrink,
		axis);
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("shrinking end"));
}

void sge::gui::layouts::grid::expand(
	dim const &optimal,
	dim const &usable,
	axis_type const axis)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("there is too much space, expanding begin"));

	unsigned count;
	if ((count = count_flags(axis_policy::should_grow,axis)))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("there are ") 
							<< count 
							<< SGE_TEXT(" widgets which should grow, growing those"));

		adapt(
			optimal,
			usable,
			axis_policy::should_grow,
			axis);
	}
	else if ((count = count_flags(axis_policy::can_grow,axis)))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("there are ") 
							<< count 
							<< SGE_TEXT(" widgets which can grow, growing those"));

		adapt(
			optimal,
			usable,
			axis_policy::can_grow,
			axis);
	}
	else
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("there are no widgets which could grow :("));
	}
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("expanding end"));
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

	SGE_ASSERT_MESSAGE(
		count,
		SGE_TEXT("adapt called when there are no widgets to adapt"));

	// how much extra space do we have on this axis?
	unit const diff = usable[axis] - optimal[axis];
	// distribute the extra space among all flexible widgets (the assert above
	// ensures that we don't divide by zero)
	unit const addition = static_cast<unit>(diff/count);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adding ") << diff << SGE_TEXT("/") 
		        << count << SGE_TEXT("=") << addition 
						<< SGE_TEXT(" pixels to the flagged rolumns"));

	cache::rolumn_container const &rolumns =
		valid_cache().rolumns();

	for (
		size_type i = 0; 
		i < children_.dim()[axis]; 
		++i
		)
	{
		if (rolumns.pos(axis,i).policy & flag)
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("rolumn ") << i << SGE_TEXT(" can be modified")); 

			update_rolumn(
				axis,
				i,
				flag,
				addition);
		}
	}
}

namespace 
{
template<
	typename T,
	typename U,
	typename Index>
T field_swap_pos(
	sge::container::field<T> &f,
	bool swap,
	Index const a,
	Index const b)
{
	return 
		swap
			? f.pos(b,a)
			: f.pos(a,b);
}
}

void sge::gui::layouts::grid::update_rolumn(
	axis_type const axis,
	unsigned const rolumn,
	axis_policy::type const flag,
	unit const addition)
{
	// update the cache
	valid_cache().rolumns().pos(
		axis,
		rolumn).size += addition;

	for (
		size_type i = 0; 
		i < children_.dim()[axis];
		++i)
	{
		widgets::base * const w = field_swap_pos(
			valid_cache().plane(),
			axis,
			static_cast<size_type>(
				i),
			static_cast<size_type>(
				rolumn));
		
		// not a widget we're looking for
		if (!w || !(w->size_policy().index(axis) & flag))
			continue;

		valid_cache().data()[w].size[axis] += addition;
	}
}

// counts the number of widgets on the specified axis (not rolumn, axis) which
// have the specified axis policy flag (uses the cache!)
unsigned sge::gui::layouts::grid::count_flags(
	axis_policy::type const flags,
	axis_type const axis) const
{
	unsigned count = 0;

	cache::rolumn_container const &rolumns = 
		valid_cache().rolumns();

	for (
		cache::rolumn_container::size_type i = 0;
		i < rolumns.dim().w();
		++i)
		if (rolumns.pos(axis,i).policy & flags)
			++count;

	return count;
}

// iterates through the whole table, calculating the minimal size for the
// table. if we have extra space to spare, align widgets to their alignment property
void sge::gui::layouts::grid::update_widgets()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("updating widgets begin"));

	cache::child_plane &c = 
		valid_cache().plane();
	
	cache::rolumn_container const &rolumns = 
		valid_cache().rolumns();

	point pos = point::null();
	for (size_type x = 0; x < c.w(); ++x)
	{
		pos.y() = static_cast<unit>(0);
		for (size_type y = 0; y < c.h(); ++y)
		{
			widget * const w = 
				c.pos(cache::child_plane::vector_type(x,y));
			if (w)
				update_widget(
					*w,
					pos,
					dim(
						rolumns.pos(
							cache::rolumn_container::vector_type(
								x_axis,
								x)),
						rolumns.pos(
							cache::rolumn_container::vector_type(
								y_axis,
								y))));

			pos.y() += rolumns.pos(y_axis,y);
		}
		pos.x() += rolumns.pos(x_axis,x);
	}
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("updating widgets end"));
}

namespace
{
sge::gui::point const center(
	sge::gui::point const &pos,
	sge::gui::dim const &rect,
	sge::gui::dim const &smaller)
{
	return pos + rect/2 - smaller/2;
}
}

// the widget has got it's size in data[&w].size, it just has to be aligned in
// it's cell, denoted by d.
void sge::gui::layouts::grid::update_widget(
	widget &w,
	point const &p,
	dim const &d)
{
	dim const smaller = 
		valid_cache().data()[&w].size;

	base::set_widget_pos(
		w,
		center(
			p,
			d,
			smaller));
	
	base::set_widget_size(
		w,
		smaller);
}
