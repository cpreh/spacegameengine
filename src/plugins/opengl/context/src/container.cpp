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


#include "../container.hpp"
#include "../base.hpp"
#include <sge/log/global.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

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

bool
sge::opengl::context::container::insert(
	size_type const _index,
	auto_ptr _ptr
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
		return false;
	
	elements_[_index] = _ptr.release();

	return true;
}

void
sge::opengl::context::container::destroy()
{
	BOOST_FOREACH(
		inner_container::value_type val,
		elements_
	)
		try
		{
			delete val;
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
