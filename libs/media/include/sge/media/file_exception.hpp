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


#ifndef SGE_MEDIA_FILE_EXCEPTION_HPP_INCLUDED
#define SGE_MEDIA_FILE_EXCEPTION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/media/file_exception_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/detail/instantiate/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace media
{

template<
	typename Base
>
class SGE_CORE_DETAIL_CLASS_SYMBOL file_exception
:
	public Base
{
public:
	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	file_exception(
		sge::media::optional_name const &,
		fcppt::string const &
	);

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	file_exception(
		file_exception &&
	);

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	file_exception(
		file_exception const &
	);

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	file_exception &
	operator=(
		file_exception &&
	);

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	file_exception &
	operator=(
		file_exception const &
	);

	SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
	~file_exception() noexcept
	override;
};

}
}

#endif
