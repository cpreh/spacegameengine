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


#include <sge/gui/impl/make_container_pair.hpp>
#include <sge/gui/impl/swap_pair.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>


sge::gui::widget::reference_alignment_vector
sge::gui::impl::make_container_pair(
	sge::gui::widget::reference_alignment_pair const &_first,
	sge::gui::widget::reference_alignment_pair const &_second,
	sge::gui::impl::swap_pair const _swap
)
{
	return
		_swap.get()
		?
			sge::gui::widget::reference_alignment_vector{
				_second,
				_first
			}
		:
			sge::gui::widget::reference_alignment_vector{
				_first,
				_second
			}
		;
}
