#include "cache.hpp"
#include <sge/math/negative.hpp>

sge::gui::layouts::grid::cache::widget_data::widget_data()
:
	/*
	optimal_size(
		dim::null()),
	final_size(
		dim::null())
		*/
	size(
		dim::null())
{}

sge::gui::layouts::grid::cache::rolumn_data::rolumn_data()
:
	size(
		static_cast<unit>(0))
	policy()
{}

sge::gui::layouts::grid::cache::cache(
	grid &_that)
:
	that_(_that),
	plane_(),
	data_(),
	rolumns_()
{
	first_pass();
	second_pass();
}

sge::gui::layouts::grid::cache::child_plane &
	sge::gui::layouts::grid::cache::plane()
{
	return plane_;
}

sge::gui::layouts::grid::cache::data_map &
	sge::gui::layouts::grid::cache::data()
{
	return data_;
}

sge::gui::layouts::grid::cache::rolumn_container &
	sge::gui::layouts::grid::cache::rolumns()
{
	return rolumns_;
}

void sge::gui::layouts::grid::cache::first_pass()
{
	// iterate through the widgets and:
	//  -get their optimal_sizes
	//  -get the overall dimensions of the grid
	//  -add widgets to the plane
	BOOST_FOREACH(widget &w,that_)
	{
		if(!w.pos_hint())
			throw exception(
				SGE_TEXT("a widget in a grid layout doesn't have a position hint, don't know how to position it"));

		point const hint = *w.pos_hint();

		if(math::negative(hint.x()) || math::negative(hint.y()))
			throw exception(
				SGE_TEXT("grid layout position hints have to be positive"));

		child_plane::vector_type const on_plane = 
			structure_cast<child_plane::size_type>(hint);

		// is there already a widget present at this spot?
		if(plane_.pos(on_plane))
			throw exception(
				SGE_TEXT("position ")+
				lexical_cast<string>(hint)+
				SGE_TEXT(" in grid already taken by a widget of type ")+
				type_name(
					typeid(
						*plane_.pos(
							on_plane))));

		plane_.resize(
			child_plane::dim_type(
				std::max(
					on_plane.x(),
					plane_.dim().w()),
				std::max(
					on_plane.y(),
					plane_.dim().h())));

		plane_.pos(on_plane) = w;
	}
}

void sge::gui::layouts::grid::cache::second_pass()
{
	rolumns_.resize(
		rolumn_container::dim_type(
			static_cast<rolumn_container::size_type>(
				2),
			std::max(
				plane_.dim().w(),
				plane_.dim().h())));

	rolumn_container::vector_type p;
	for(
		p.x() = static_cast<size_type>(0); 
		p.x() < plane_.dim().w(); 
		++p.x())
	{
		for(
			p.y() = static_cast<size_type>(0); 
			p.y() < plane_.dim().h(); 
			++p.y())
		{
			if (!plane_.pos(p))
				continue;

			// for each of the two axes
			for (unsigned i = 0; i < 2; ++i)
			{
				rolumn_data &d = 
					rolumns_.pos
					(
						rolumn_container::vector_type
						(
							static_cast<rolumn_container::size_type>
							(
								i
							),
							p
							[
								static_cast<rolumn_container::size_type>
								(
									i
								)
							]
						)
					);
				
				d.size = 
					std::max
					(
						d.size,
						data_
							[
								plane_.pos
								(
									p
								)
							]
						.size
							[
								static_cast<dim::size_type>
								(
									i
								)
							]
					);

				d.policy |= 
					plane_.pos(p)->size_policy()
					[
						static_cast<std::size_t>
						(
							i
						)
					]
			}
		}
	}
}
