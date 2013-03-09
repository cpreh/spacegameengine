/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_CONTEXT_CONTAINER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_CONTAINER_IMPL_HPP_INCLUDED

#include <sge/opengl/logger.hpp>
#include <sge/opengl/context/base_decl.hpp>
#include <sge/opengl/context/container_decl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>


template<
	typename Domain
>
sge::opengl::context::container<
	Domain
>::container()
:
	elements_(
		50u
	)
{
}

template<
	typename Domain
>
sge::opengl::context::container<
	Domain
>::~container()
{
	this->destroy();
}

template<
	typename Domain
>
typename sge::opengl::context::container<
	Domain
>::pointer
sge::opengl::context::container<
	Domain
>::get(
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

template<
	typename Domain
>
typename sge::opengl::context::container<
	Domain
>::pointer
sge::opengl::context::container<
	Domain
>::insert(
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

template<
	typename Domain
>
void
sge::opengl::context::container<
	Domain
>::destroy()
{
	for(
		auto elem : elements_
	)
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

#endif
