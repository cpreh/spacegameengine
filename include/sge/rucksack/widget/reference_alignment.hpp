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


#ifndef SGE_RUCKSACK_WIDGET_REFERENCE_ALIGNMENT_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_REFERENCE_ALIGNMENT_HPP_INCLUDED

#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/detail/symbol.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/rucksack/widget/reference_alignment_fwd.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

class reference_alignment
{
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	reference_alignment(
		sge::rucksack::widget::reference,
		sge::rucksack::alignment
	);

	sge::rucksack::widget::reference const
	reference() const;

	sge::rucksack::alignment
	alignment() const;
private:
	sge::rucksack::widget::reference reference_;

	sge::rucksack::alignment alignment_;
};

}
}
}

#endif
