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


#include <sge/opengl/context/container.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/log/global.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>


sge::opengl::context::container::container()
:
	elements_(
		50 // TODO
	)
{}

sge::opengl::context::container::~container()
{
	destroy();
}

sge::opengl::context::base *
sge::opengl::context::container::get(
	size_type const _index
) const
{
	return
		_index
		< elements_.size()
		?
			elements_[_index]
		:
			0
		;
}

sge::opengl::context::container::pointer
sge::opengl::context::container::insert(
	size_type const _index,
	unique_ptr _ptr
)
{
	try
	{
		// might throw bad_alloc
		if(
			_index
			>= elements_.size()
		)
			elements_.resize(
				_index
			);
	}
	catch(...)
	{
		destroy();

		throw;
	}

	if(
		elements_[_index]
	)
		return 0;

	pointer const nptr(
		_ptr.release()
	);

	elements_[_index] = nptr;

	return nptr;
}

void
sge::opengl::context::container::destroy()
{
	for(
		inner_container::iterator it(
			elements_.begin()
		);
		it != elements_.end();
		++it
	)
		try
		{
			delete *it;
		}
		catch(...)
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Destructor throwed in opengl::context::container")
			);
		}
}
