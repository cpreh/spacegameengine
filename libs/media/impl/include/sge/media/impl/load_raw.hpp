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


#ifndef SGE_MEDIA_IMPL_LOAD_RAW_HPP_INCLUDED
#define SGE_MEDIA_IMPL_LOAD_RAW_HPP_INCLUDED

#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/impl/raw_streambuf.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{
namespace impl
{

template<
	typename Result,
	typename System
>
fcppt::optional::object<
	Result
>
load_raw(
	System &_system,
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	sge::media::impl::raw_streambuf buf{
		_range
	};

	return
		fcppt::variant::to_optional<
			Result
		>(
			_system.load_stream(
				fcppt::make_unique_ptr<
					std::istream
				>(
					&buf
				),
				_extension,
				sge::media::optional_name()
			)
		);
}

}
}
}

#endif
