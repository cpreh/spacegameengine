/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_VIEW_MAKE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_MAKE_HPP_INCLUDED

#include "make_visitor.hpp"
#include <sge/image/size_type.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/mpl/invoke_on.hpp>
#include <mizuiro/image/is_raw_view.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>

namespace sge
{
namespace image
{
namespace view
{

template<
	typename Result,
	typename Elements,
	typename Dim,
	typename OptionalPitch
>
Result const
make(
	image::raw_pointer const _data,
	Dim const &_dim,
	image::color::format::type const _format,
	OptionalPitch const &_pitch
)
{
	// TODO: gcc-4.5: Check if this is a gcc bug

	return
		fcppt::mpl::invoke_on<
			boost::mpl::filter_view<
				Elements,
				boost::mpl::bind<
					boost::mpl::quote1<
						mizuiro::image::is_raw_view
					>,
					boost::mpl::_1
				>
			>
		>(
			static_cast<
				image::size_type
			>(
				_format
			),
			sge::image::view::make_visitor<
				Result,
				Dim,
				OptionalPitch
			>(
				_data,
				_dim,
				_pitch
			)
		);
}

}
}
}

#endif
