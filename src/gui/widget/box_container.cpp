/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/gui/context_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/container.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/reference_vector.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <fcppt/algorithm/map.hpp>


sge::gui::widget::box_container::box_container(
	sge::gui::context &_context,
	sge::gui::widget::reference_alignment_vector const &_widgets,
	sge::rucksack::axis const _axis
)
:
	sge::gui::widget::container(
		_context,
		fcppt::algorithm::map<
			sge::gui::widget::reference_vector
		>(
			_widgets,
			[](
				sge::gui::widget::reference_alignment_pair const &_pair
			)
			{
				return
					_pair.reference();
			}
		),
		// This is pretty dangerous but the base class only uses the
		// reference here
		layout_
	),
	layout_(
		_axis,
		sge::rucksack::padding{
			4
		}
	)
{
	for(
		auto const &element
		:
		_widgets
	)
		layout_.push_back_child(
			element.reference().get().layout(),
			element.alignment()
		);
}

sge::gui::widget::box_container::~box_container()
{
}

void
sge::gui::widget::box_container::push_front(
	sge::gui::widget::reference_alignment_pair const &_pair
)
{
	this->push_front_widget(
		_pair.reference()
	);

	layout_.push_front_child(
		_pair.reference().get().layout(),
		_pair.alignment()
	);
}

void
sge::gui::widget::box_container::pop_front()
{
	layout_.pop_front_child();

	this->pop_front_widget();
}

void
sge::gui::widget::box_container::push_back(
	sge::gui::widget::reference_alignment_pair const &_pair
)
{
	this->push_back_widget(
		_pair.reference()
	);

	layout_.push_back_child(
		_pair.reference().get().layout(),
		_pair.alignment()
	);
}

void
sge::gui::widget::box_container::replace(
	sge::rucksack::widget::box::size_type const _index,
	sge::gui::widget::reference_alignment_pair const &_pair
)
{
	this->replace_widgets(
		_index,
		_pair.reference()
	);

	layout_.replace_children(
		layout_.child_position(
			_index
		),
		_pair.reference().get().layout(),
		_pair.alignment()
	);
}

void
sge::gui::widget::box_container::pop_back()
{
	layout_.pop_back_child();

	this->pop_back_widget();
}

void
sge::gui::widget::box_container::clear()
{
	layout_.clear();

	this->clear_widgets();
}

sge::rucksack::widget::box &
sge::gui::widget::box_container::box_layout()
{
	return
		layout_;
}
