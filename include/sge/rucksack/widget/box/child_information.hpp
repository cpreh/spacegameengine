/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RUCKSACK_WIDGET_BOX_CHILD_INFORMATION_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_BOX_CHILD_INFORMATION_HPP_INCLUDED

#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/dim.hpp>
#include <fcppt/math/dim/object_impl.hpp>

namespace sge
{
namespace rucksack
{
namespace widget
{
namespace box
{
/**
 * This is a utility class which holds all the information needed for a child.
 * It's intentionally not supplied with SYMBOLs because it's not part of the
 * interface the user sees.
 */
class child_information
{
public:
	child_information();

	child_information(
		sge::rucksack::alignment,
		sge::rucksack::dim const &);

	sge::rucksack::alignment
	alignment() const;

	sge::rucksack::dim const &
	size() const;

	void
	size(
		sge::rucksack::dim const &);
private:
	sge::rucksack::alignment alignment_;
	sge::rucksack::dim size_;
};
}
}
}
}

#endif
