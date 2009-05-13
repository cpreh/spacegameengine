#include <sge/gui/log.hpp>
#include <sge/gui/axis_type.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/dim/dim.hpp>
#include <sge/type_name.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

class sge::gui::layouts::grid::cache
{
public:
	cache(grid &);
private:
	grid &that_;

	typedef container::field<
		widgets::base*,
		container::raw_vector
		> child_container;
	typedef container::field<
		widgets::base const *,
		container::raw_vector
		> const_child_container;
	typedef child_container::size_type size_type;
	typedef std::map<
		widgets::base*,
		dim
		> sizes_map;
	typedef container::field<
		size_policy,
		std::vector
		> policy_cache_type;
	typedef container::field<
		dim,
		std::vector
		> rolumn_cache_type;
};

sge::gui::layouts::grid::cache::cache(grid &_that)
:
	that_(_that)
{
}

namespace
{
template<typename T>
bool negative(T const &t)
{
	return t < static_cast<T>(0);
}

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

	update_cache();

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
	const_child_container const c = children();
	dim maxdims = dim::null();

	for (size_type y = 0; y != c.h(); ++y)
	{
		dim thisdims = dim::null();
		for (size_type x = 0; x != c.w(); ++x)
		{
			SGE_ASSERT_MESSAGE(
				c.pos(x,y),
				SGE_TEXT("currently, all grid cells have to have widgets in them"));

			dim const s = c.pos(x,y)->optimal_size();
			thisdims.w() += s.w();
			thisdims.h() = std::max(thisdims.h(),s.h());
		}
		maxdims.w() = std::max(maxdims.w(),thisdims.w());
		maxdims.h() += thisdims.h();
	}

	return maxdims;
}

// Takes all of the widgets' position hints and creates a dimension in the form
// ([0,max_x],[0,max_y]). This function also checks if the position hints are
// positive
sge::gui::dim const sge::gui::layouts::grid::dimensions() const
{
	sge::gui::dim maxd = sge::gui::dim::null();
	BOOST_FOREACH(widgets::base const &w,connected_widget().children())
	{
		if (!w.pos_hint())
			throw exception(
				SGE_TEXT("a widget in a grid layout doesn't have a position hint, don't know how to position it"));

		point const hint = *w.pos_hint();
	
		if (negative(hint.x()) || negative(hint.y()))
			throw exception(
				SGE_TEXT("grid layout position hints have to be positive"));

		maxd.w() = 
			std::max(
				hint.x(),
				maxd.w());
		maxd.h() = 
			std::max(
				hint.y(),
				maxd.h());
	}
	return maxd;
}

// Uses dimensions() to create a two-dimensional array of widgets
sge::gui::layouts::grid::const_child_container const 
sge::gui::layouts::grid::children() const
{
	dim const dims = dimensions();

	const_child_container a(
		structure_cast<const_child_container::dim_type>(
			dims));
	
	// since we iterate over the widgets, not the array itself, there might be
	// empty spots, which we initialize with a null pointer here
	std::fill(
		a.begin(),
		a.end(),
		static_cast<widgets::base const *>(0));

	BOOST_FOREACH(widgets::base const &w,connected_widget().children())
	{
		if (!w.pos_hint())
			throw exception(
				SGE_TEXT("a widget in a grid layout has no position hint, I don't know where to put it"));

		child_container::vector_type const p = 
			structure_cast<child_container::vector_type>(
				*w.pos_hint());

		if (a.pos(p))
			throw exception(
				SGE_TEXT("two widgets in a grid layout have the same position hint, this is invalid"));

		a.pos(p) = &w;
	}
	return a;
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

	for (
		size_type i = 0; 
		i < children_.dim()[axis]; 
		++i
		)
		if (policy_cache_.pos(axis,i) & flag)
			update_rolumn(
				axis,
				i,
				flag,
				addition);
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
	policy_cache_type::size_type const rolumn,
	axis_policy::type const flag,
	unit const addition)
{
	rolumn_cache_.pos(axis,rolumn) += addition;
	for (
		size_type i = 0; 
		i < children_.dim()[axis];
		++i
		)
	{
		widgets::base * const w = field_swap_pos(
			children_,
			axis,
			static_cast<size_type>(i),
			static_cast<size_type>(
				rolumn));
		
		if (!w || !(w->size_policy().index(axis) & flag))
			continue;

		sizes_[w][axis] += addition;
	}
}

// counts the number of widgets on the specified axis (not rolumn, axis) which
// have the specified axis policy flag (uses the cache!)
unsigned sge::gui::layouts::grid::count_flags(
	axis_policy::type const flags,
	axis_type const axis) const
{
	unsigned count = 0;

	for (
		size_type i = 0;
		i < children_.dim()[axis];
		++i)
		if (policy_cache_.pos(axis,i) & flags)
			++count;
	
	return count;
}

void sge::gui::layouts::grid::update_cache()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("updating cache"));

	children_ = children();
	update_policy_cache();
	update_size_cache();

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("cache updated"));
}

void sge::gui::layouts::grid::update_policy_cache()
{
	// prepare for two axes and the children's dimensions (the array doesn't have
	// to be a square, but since it's only for counting flags, the rest can be
	// filled with empty axis policies)
	policy_cache_.resize(
		policy_cache_type::dim_type(
			2,
			children_.dim()[0],
			children_.dim()[1]));
	
	// TODO: is this really neccessary? Or is the array default-initialized?
	std::fill(
		policy_cache_.begin(),
		policy_cache_.end(),
		size_policy());

	for (child_container::size_type y = 0; y < children_.h(); ++y)
	{
		for (child_container::size_type x = 0; x < children_.w(); ++x)
		{
			if (!children_.pos(x,y))
				continue;
			
			policy_cache_.pos(y_axis,y) |= children_.pos(x,y)->size_policy();
			policy_cache_.pos(x_axis,x) |= children_.pos(x,y)->size_policy();
		}
	}
}

void sge::gui::layouts::grid::update_size_cache()
{
	BOOST_FOREACH(widgets::base &w,connected_widget().children())
		sizes_[&w] = w->optimal_size();
}

void sge::gui::layouts::grid::update_rolumn_cache()
{
	rolumn_cache_.resize(
		rolumn_cache_type::dim_type(
			2,
			std::max(
				children_.w(),
				children_.h())));
	
	for (size_type x = 0; x < children_.w(); ++x)
	{
		unit &max = 
			rolumn_cache_.pos(
				x,
				0);

		max = 0;
		for (size_type y = 0; y < children_.h(); ++y)
		{
			SGE_ASSERT_MESSAGE(
				children_.pos(x,y),
				SGE_TEXT("currently, all grid cells have to have widgets in them"));

			max = 
				std::max(
					max,
					sizes_[children_.pos(x,y)].w());
		}
	}

	for (size_type y = 0; y < children_.h(); ++y)
	{
		unit &max = 
			rolumn_cache_.pos(
				1,
				y);

		max = 0;
		for (size_type x = 0; x < children_.w(); ++x)
		{
			SGE_ASSERT_MESSAGE(
				children_.pos(x,y),
				SGE_TEXT("currently, all grid cells have to have widgets in them"));

			max = 
				std::max(
					max,
					sizes_[children_.pos(x,y)].h());
		}
	}
}

// iterates through the whole table, calculating the minimal size for the
// table. if we have extra space to spare, align widgets to their alignment property
void sge::gui::layouts::grid::update_widgets()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("updating widgets begin"));

	point pos = point::null();
	for (size_type x = 0; x < children_.w(); ++x)
	{
		pos.y() = static_cast<unit>(0);
		for (size_type y = 0; y < children.h(); ++y)
		{
			SGE_ASSERT_MESSAGE(
				children_.pos(x,y),
				SGE_TEXT("currently, all grid cells have to have widgets in them"));

			update_widget(
				*children_.pos(x,y),
				pos,
				dim(
					rolumn_cache_.pos(x_axis,x),
					rolumn_cache_.pos(y_axis,y)));

			pos.y() += rolumn_cache_.pos(y_axis,y);
		}
		pos.x() += rolumn_cache_.pos(x_axis,x);
	}
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("updating widgets end"));
}

void sge::gui::layouts::grid::update_widget(
	widget &w,
	point const &p,
	dim const &d)
{
	/*
	switch (w.alignment().x())
	{
		case alignment_h::left:
		// TODO
		break;
	}
	*/
}
