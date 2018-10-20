/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_MEDIA_IMPL_FILE_EXCEPTION_IMPL_HPP_INCLUDED
#define SGE_MEDIA_IMPL_FILE_EXCEPTION_IMPL_HPP_INCLUDED

#include <sge/media/error_string.hpp>
#include <sge/media/file_exception.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/string.hpp>


template<
	typename Base
>
sge::media::file_exception<
	Base
>::file_exception(
	sge::media::optional_name const &_name,
	fcppt::string const &_text
)
:
	Base(
		sge::media::error_string(
			_name,
			_text
		)
	)
{
}

template<
	typename Base
>
sge::media::file_exception<
	Base
>::file_exception(
	file_exception &&
)
= default;

template<
	typename Base
>
sge::media::file_exception<
	Base
>::file_exception(
	file_exception const &
)
= default;

template<
	typename Base
>
sge::media::file_exception<
	Base
> &
sge::media::file_exception<
	Base
>::operator=(
	file_exception &&
)
= default;

template<
	typename Base
>
sge::media::file_exception<
	Base
> &
sge::media::file_exception<
	Base
>::operator=(
	file_exception const &
)
= default;

template<
	typename Base
>
sge::media::file_exception<
	Base
>::~file_exception() noexcept
{
}

#endif
