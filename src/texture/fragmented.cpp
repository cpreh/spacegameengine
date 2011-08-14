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


#include <sge/texture/fragmented.hpp>
#include <sge/texture/manager.hpp>
#include <fcppt/assert/error.hpp>

sge::texture::fragmented::fragmented()
:
	manager_(0),
	iterator_()
{
}

sge::texture::fragmented::~fragmented()
{
}

void
sge::texture::fragmented::return_fragment(
	texture::part const &_part
)
{
	this->on_return_fragment(
		_part
	);

	if(
		this->manager()
	)
	{
		FCPPT_ASSERT_ERROR(
			iterator_
		);

		this->manager()->part_freed(
			*iterator_,
			*this
		);
	}
}

bool
sge::texture::fragmented::full() const
{
	return
		this->free_value() == 0;
}

void
sge::texture::fragmented::manager(
	texture::manager *const _manager
)
{
	manager_ = _manager;
}

sge::texture::manager *
sge::texture::fragmented::manager() const
{
	return manager_;
}

void
sge::texture::fragmented::container_position(
	detail::container_position const &_iterator
)
{
	iterator_ = _iterator;
}
