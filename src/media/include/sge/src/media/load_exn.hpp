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


#ifndef SGE_SRC_MEDIA_LOAD_EXN_HPP_INCLUDED
#define SGE_SRC_MEDIA_LOAD_EXN_HPP_INCLUDED

#include <sge/src/media/load.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

template<
	typename Result,
	typename Exception,
	typename System
>
Result
load_exn(
	System &_system,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::optional::to_exception(
			sge::media::load<
				Result,
				Exception
			>(
				_system,
				_path
			),
			[
				&_path
			]{
				return
					Exception(
						FCPPT_TEXT("Unable to load ")
						+
						fcppt::filesystem::path_to_string(
							_path
						)
					);
			}
		);
}

}
}

#endif
