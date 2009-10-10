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


#include <sge/log/context.hpp>
#include <sge/log/location.hpp>
#include <sge/container/tree_impl.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/text.hpp>
#include <algorithm>

sge::log::context::context()
:
	tree_(
		detail::inner_context_node(
			SGE_TEXT("sge")
		)
	)
{}

sge::log::context::~context()
{
}

void
sge::log::context::add(
	location const &location_,
	object &object_
)
{
	detail::context_tree *cur(
		&tree_
	);

	for(
		location::const_iterator item(
			location_.begin()
		);
		item != location_.end();
		++item
	)
	{
	/*
		detail::context_tree::iterator const item_it(
			std::find(
				cur->begin(),
				cur->end(),
				*item
			)
		);

		if(
			item_it == cur->end()
		)
		{
			cur->push_back(
				detail::inner_context_node(
					*item
				)
			);

			cur = &cur->back();
		}
		else
			cur = &*item_it;
	*/
	}

	cur->push_back(
		detail::outer_context_node(
			object_
		)
	);
}

void
sge::log::context::remove(
	location const &location_,
	object &object_
)
{
}

sge::log::object &
sge::log::context::find(
	location const &location_
) const
{
}
