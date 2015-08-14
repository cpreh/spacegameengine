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


#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/expander.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/literal.hpp>


sge::gui::widget::expander::expander(
	sge::rucksack::axis const _axis
)
:
	sge::gui::widget::dummy(),
	layout_{
		sge::rucksack::make_axis_policy(
			sge::rucksack::axis_policy_function{
				[
					_axis
				](
					sge::rucksack::axis const _cur_axis
				)
				{
					sge::rucksack::scalar const size{
						fcppt::literal<
							sge::rucksack::scalar
						>(
							0
						)
					};

					return
						_cur_axis
						==
						_axis
						?
							sge::rucksack::axis_policy{
								sge::rucksack::minimum_size{
									size
								}
							}
						:
							sge::rucksack::axis_policy{
								sge::rucksack::preferred_size{
									size
								}
							}
						;
				}
			}
		)
	}
{
}

sge::gui::widget::expander::~expander()
{
}

sge::rucksack::widget::base &
sge::gui::widget::expander::layout()
{
	return
		layout_;
}
