#include <sge/gui/layouts/grid.hpp>

namespace
{
template<typename T>
bool negative(T const &t)
{
	return t < static_cast<T>(0);
}
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
}

sge::gui::dim const sge::gui::layouts::grid::optimal_size() const
{
	const_child_container const c = children();
	dim maxdims = dim::null();

	for (const_child_container::const_iterator y = c.begin(); y != c.end(); ++y)
	{
		dim thisdims = dim::null();
		for (const_child_row::const_iterator x = y->begin(); x != y->end(); ++x)
		{
			dim const s = x->optimal_size();
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
	BOOST_FOREACH(widget const &w,connected_widget().children())
	{
		if (negative(w.pos_hint().x()) || negative(w.pos_hint().y()))
			throw exception(
				SGE_TEXT("grid layout position hints have to be positive"));

		maxd.w() = 
			std::max(
				w.pos_hint().x(),
				maxd.w());
		maxd.h() = 
			std::max(
				w.pos_hint().y(),
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
		boost::extents
			[static_cast<const_child_container::size_type>(dims.h())]
			[static_cast<const_child_container::size_type>(dims.w())]);

	std::fill(
		a.data(),
		a.data()+a.num_elements(),
		0);

	BOOST_FOREACH(widgets::base const *w,children())
	{
		if (!w->pos_hint())
			throw exception(
				SGE_TEXT("a widget in a grid layout has no position hint, I don't know where to put it"));

		point const p = *w->pos_hint();

		if (a(p.x(),p.y()))
			throw exception(
				SGE_TEXT("two widgets in a grid layout have the same position hint, this is invalid"));

		a(p.x(),p.y()) = w;
	}
	return a;
}

sge::gui::layouts::grid::child_container const sge::gui::layouts::grid::children()
{
	return const_cast<grid const &>(*this).children();
}
