/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_COLOR_ANY_CONVERT_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_ANY_CONVERT_VISITOR_HPP_INCLUDED

#include <sge/image/invalid_convert.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/is_convertible.hpp>
#include <sge/image/color/format_static.hpp>
#include <sge/image/color/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace any
{

template<
	typename Dest
>
class convert_visitor
{
public:
	typedef typename sge::image::color::object<
		Dest
	>::type result_type;

	template<
		typename Source
	>
	typename boost::enable_if<
		sge::image::color::is_convertible<
			typename Source::format,
			Dest
		>,
		result_type
	>::type const
	operator()(
		Source const &_source
	) const
	{
		return
			sge::image::color::convert<
				Dest
			>(
				_source
			);
	}

	template<
		typename Source
	>
	typename boost::disable_if<
		sge::image::color::is_convertible<
			typename Source::format,
			Dest
		>,
		result_type
	>::type const
	operator()(
		Source const &
	) const
	{
		throw sge::image::invalid_convert(
			sge::image::color::format_static<
				typename Source::format
			>::value,
			sge::image::color::format_static<
				Dest
			>::value
		);
	}
};

}
}
}
}

#endif
