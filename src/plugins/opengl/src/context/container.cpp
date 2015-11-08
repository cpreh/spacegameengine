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


#include <sge/opengl/logger.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


sge::opengl::context::container::container()
:
	elements_(
		50u
	)
{
}

sge::opengl::context::container::~container()
{
	this->destroy();
}

sge::opengl::context::container::pointer
sge::opengl::context::container::get(
	size_type const _index
) const
{
	return
		_index
		<
		elements_.size()
		?
			elements_[
				_index
			]
		:
			nullptr
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
			>=
			elements_.size()
		)
			elements_.resize(
				_index
			);
	}
	catch(...)
	{
		this->destroy();

		throw;
	}

	if(
		elements_[
			_index
		]
	)
		return
			nullptr;

	pointer const nptr(
		_ptr.release_ownership()
	);

	elements_[
		_index
	] =
		nptr;

	return
		nptr;
}

void
sge::opengl::context::container::destroy()
{
	for(
		auto elem
		:
		elements_
	)
	{
		try
		{
			delete elem;
		}
		catch(...)
		{
			FCPPT_LOG_ERROR(
				sge::opengl::logger(),
				fcppt::log::_
					<< FCPPT_TEXT("Destructor throwed in opengl::context::container")
			);
		}
	}
}
