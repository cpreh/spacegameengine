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


#ifndef SGE_SRC_IMAGE_DYNAMIC_COLOR_ACCESS_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_COLOR_ACCESS_HPP_INCLUDED

#include <sge/src/image/dynamic/color/available_channels.hpp>
#include <sge/src/image/dynamic/color/channel_index.hpp>
#include <mizuiro/size_type.hpp>
#include <mizuiro/color/format_store.hpp>
#include <mizuiro/color/access/dynamic_index.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace mizuiro
{
namespace color
{
namespace access
{

template<
	typename Format,
	typename Channel
>
struct dynamic_index<
	Format,
	Channel,
	typename boost::enable_if<
		boost::is_same<
			typename Format::available_channels,
			sge::image::dynamic::color::available_channels::type
		>
	>::type
>
{
	static
	mizuiro::size_type
	execute(
		mizuiro::color::format_store<Format> const &,
		Channel const &
	)
	{
		return
			sge::image::dynamic::color::channel_index(
				Channel()
			);
	}
};

}
}
}

#endif
