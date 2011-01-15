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


#include <sge/gui/detail/grid_cache.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/exception.hpp>
#include <sge/gui/log.hpp>
#include <fcppt/container/grid/resize_preserve_init.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/is_negative.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/type_name.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <cstddef>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("detail: grid_cache")
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
	policy(
		axis_policy::type::null()
	)
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
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("first pass, begin"));
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
				FCPPT_TEXT("a widget in a grid layout doesn't have a position hint, don't know how to position it"));

		point const hint = *w.pos_hint();

		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_
				<< FCPPT_TEXT("widget of type ")
				<< fcppt::type_name(typeid(w))
				<< FCPPT_TEXT(" has position hint ")
				<< hint
		);

		if(fcppt::math::is_negative(hint.x()) || fcppt::math::is_negative(hint.y()))
			throw exception(
				FCPPT_TEXT("grid layout position hints have to be positive"));

		index_vector const on_plane =
			fcppt::math::vector::structure_cast<index_vector>(hint);

		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_
				<< FCPPT_TEXT("converted position hint is ")
				<< on_plane
				<< FCPPT_TEXT(", resizing plane (original dim ")
				<< plane_.dimension()[0] << FCPPT_TEXT('x') << plane_.dimension()[1]
				<< FCPPT_TEXT(") to ")
			        << index_dim(
					std::max(
						static_cast<child_plane::size_type>(on_plane.x()+1),
						plane_.dimension()[0]
					),
					std::max(
						static_cast<child_plane::size_type>(on_plane.y()+1),
						plane_.dimension()[1]
					)
				)
		);

		fcppt::container::grid::resize_preserve_init(
			plane_,
			index_dim(
				std::max(
					static_cast<child_plane::size_type>(on_plane.x()+1),
					plane_.dimension()[0]),
				std::max(
					static_cast<child_plane::size_type>(on_plane.y()+1),
					plane_.dimension()[1])
			),
			static_cast<
				child_plane::value_type
			>(
				0
			)
		);

		if(plane_[child_plane::dim(on_plane.x(),on_plane.y())])
			throw exception(
				FCPPT_TEXT("position ")+
				fcppt::lexical_cast<fcppt::string>(hint)+
				FCPPT_TEXT(" in grid already taken by a widget of type ")+
				fcppt::type_name(
					typeid(
						*plane_[child_plane::dim(on_plane.x(),on_plane.y())]
						)
					)
				);

		plane_[child_plane::dim(on_plane.x(),on_plane.y())] = 
			const_cast<widgets::base *>(&w);

		dim const optsize =
			w.optimal_size();

		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("this widget has optimal size ")
			        << optsize);

		data_[const_cast<widgets::base *>(&w)].size = optsize;
	}

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("first pass, end"));
}

void sge::gui::detail::grid_cache::second_pass()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("second pass, begin"));

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("setting rolumn container dimensions to ")
		        << std::max(plane_.dimension()[0],plane_.dimension()[1]));

	fcppt::container::grid::resize_preserve_init(
		rolumns_,
		index_dim(
			static_cast<rolumn_container::size_type>(
				2),
			std::max(
				plane_.dimension()[0],
				plane_.dimension()[1])
		),
		rolumn_container::value_type()
	);

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("iterating through the widget plane "));

	index_vector p;
	for(
		p.x() = static_cast<size_type>(0);
		p.x() < plane_.dimension()[0];
		++p.x())
	{
		for(
			p.y() = static_cast<size_type>(0);
			p.y() < plane_.dimension()[1];
			++p.y())
		{
			if (!plane_[child_plane::dim(p.x(),p.y())])
			{
				FCPPT_LOG_DEBUG(
					mylogger,
					fcppt::log::_ << FCPPT_TEXT("there is no widget at position ")
					        << p << FCPPT_TEXT(", skipping"));
				continue;
			}

			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ << FCPPT_TEXT("there is a widget at position ")
								<< p
								<< FCPPT_TEXT(", iterating through the axes"));

			// for each of the two axes
			for (unsigned i = 0; i < 2; ++i)
			{
				index_vector const &rolumn_pos =
					index_vector
					(
						static_cast<rolumn_container::size_type>(
							i),
						p
						[
							static_cast<index_vector::size_type>(
								i)
						]
					);

				FCPPT_LOG_DEBUG(
					mylogger,
					fcppt::log::_ << FCPPT_TEXT("rolumn position is ")
									<< rolumn_pos);

				rolumn_data &d =
					rolumns_[child_plane::dim(rolumn_pos.x(),rolumn_pos.y())];

				FCPPT_LOG_DEBUG(
					mylogger,
					fcppt::log::_ << FCPPT_TEXT("current size at this rolumn is ")
									<< d.size);

				FCPPT_LOG_DEBUG(
					mylogger,
					fcppt::log::_ << FCPPT_TEXT("stored widget size in data cache is ")
									<< data_
							[
								plane_[child_plane::dim(p.x(),p.y())]
							]
						.size[static_cast<dim::size_type>(i)]);

				d.size =
					std::max
					(
						d.size,
						data_
							[
								plane_[child_plane::dim(p.x(),p.y())]
							]
						.size
							[
								static_cast<dim::size_type>(
									i)
							]
					);

				d.policy |=
					plane_[child_plane::dim(p.x(),p.y())]->size_policy().index
					(
						static_cast<std::size_t>
						(
							i
						)
					);
			}
		}
	}
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("second pass, end"));
}
