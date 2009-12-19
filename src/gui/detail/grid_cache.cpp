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


#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <sge/gui/detail/grid_cache.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/exception.hpp>
#include <sge/gui/log.hpp>
#include <fcppt/math/negative.hpp>
#include <fcppt/math/dim/output.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/object.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/type_name.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <cstddef>

namespace
{

sge::log::object mylogger(
	sge::log::parameters::inherited(
		sge::gui::global_log(),
		SGE_TEXT("detail: grid_cache")
	)
);

}

sge::gui::detail::grid_cache::widget_data::widget_data()
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

sge::gui::detail::grid_cache::rolumn_data::rolumn_data()
:
	size(
		static_cast<unit>(0)),
	policy()
{}

sge::gui::detail::grid_cache::grid_cache(
	widgets::base::child_container const &_widgets)
:
	widgets_(_widgets),
	plane_(),
	data_(),
	rolumns_(),
	volatile_rolumns_()
{
	first_pass();
	second_pass();
}

sge::gui::detail::grid_cache::child_plane &
	sge::gui::detail::grid_cache::plane()
{
	return plane_;
}

sge::gui::detail::grid_cache::data_map &
	sge::gui::detail::grid_cache::data()
{
	return data_;
}

sge::gui::detail::grid_cache::rolumn_container &
	sge::gui::detail::grid_cache::rolumns()
{
	return rolumns_;
}

sge::gui::detail::grid_cache::rolumn_container &
	sge::gui::detail::grid_cache::volatile_rolumns()
{
	return volatile_rolumns_;
}

void sge::gui::detail::grid_cache::first_pass()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("first pass, begin"));
	// iterate through the widgets and:
	//  -get their optimal_sizes
	//  -get the overall dimensions of the grid
	//  -add widgets to the plane
	//for (widgets::base::child_container::const_iterator i = widgets_.begin(); i != widgets_.end(); ++i)
	BOOST_FOREACH(widgets::base const &w,widgets_)
	{
	//	widgets::base &w = *i;
		if(!w.pos_hint())
			throw exception(
				SGE_TEXT("a widget in a grid layout doesn't have a position hint, don't know how to position it"));

		point const hint = *w.pos_hint();

		SGE_LOG_DEBUG(
			mylogger,
			log::_ << SGE_TEXT("widget of type ")
			        << type_name(typeid(w))
							<< SGE_TEXT(" has position hint ")
							<< hint);

		if(math::negative(hint.x()) || math::negative(hint.y()))
			throw exception(
				SGE_TEXT("grid layout position hints have to be positive"));

		child_plane::vector_type const on_plane =
			math::vector::structure_cast<child_plane::vector_type>(hint);

		SGE_LOG_DEBUG(
			mylogger,
			log::_ << SGE_TEXT("converted position hint is ")
			        << on_plane
							<< SGE_TEXT(", resizing plane (original dim ")
							<< plane_.dim()
							<< SGE_TEXT(") to ")
			        << child_plane::dim_type(
				std::max(
					static_cast<child_plane::size_type>(on_plane.x()+1),
					plane_.dim().w()),
				std::max(
					static_cast<child_plane::size_type>(on_plane.y()+1),
					plane_.dim().h())));

		plane_.resize(
			child_plane::dim_type(
				std::max(
					static_cast<child_plane::size_type>(on_plane.x()+1),
					plane_.dim().w()),
				std::max(
					static_cast<child_plane::size_type>(on_plane.y()+1),
					plane_.dim().h())));

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

		plane_.pos(
			on_plane) = const_cast<widgets::base *>(&w);

		dim const optsize =
			w.optimal_size();

		SGE_LOG_DEBUG(
			mylogger,
			log::_ << SGE_TEXT("this widget has optimal size ")
			        << optsize);

		data_[const_cast<widgets::base *>(&w)].size = optsize;
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("first pass, end"));
}

void sge::gui::detail::grid_cache::second_pass()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("second pass, begin"));

	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("setting rolumn container dimensions to ")
		        << std::max(plane_.dim().w(),plane_.dim().h()));

	rolumns_.resize(
		rolumn_container::dim_type(
			static_cast<rolumn_container::size_type>(
				2),
			std::max(
				plane_.dim().w(),
				plane_.dim().h())));

	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("iterating through the widget plane "));

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
			{
				SGE_LOG_DEBUG(
					mylogger,
					log::_ << SGE_TEXT("there is no widget at position ")
					        << p << SGE_TEXT(", skipping"));
				continue;
			}

			SGE_LOG_DEBUG(
				mylogger,
				log::_ << SGE_TEXT("there is a widget at position ")
								<< p
								<< SGE_TEXT(", iterating through the axes"));

			// for each of the two axes
			for (unsigned i = 0; i < 2; ++i)
			{
				rolumn_container::vector_type const &rolumn_pos =
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
					);

				SGE_LOG_DEBUG(
					mylogger,
					log::_ << SGE_TEXT("rolumn position is ")
									<< rolumn_pos);

				rolumn_data &d =
					rolumns_.pos(
						rolumn_pos);

				SGE_LOG_DEBUG(
					mylogger,
					log::_ << SGE_TEXT("current size at this rolumn is ")
									<< d.size);

				SGE_LOG_DEBUG(
					mylogger,
					log::_ << SGE_TEXT("stored widget size in data cache is ")
									<< data_
							[
								plane_.pos
								(
									p
								)
							]
						.size[static_cast<dim::size_type>(i)]);

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
					plane_.pos(p)->size_policy().index
					(
						static_cast<std::size_t>
						(
							i
						)
					);
			}
		}
	}
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("second pass, end"));
}
