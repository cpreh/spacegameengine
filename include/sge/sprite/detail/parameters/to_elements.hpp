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


#ifndef SGE_SPRITE_DETAIL_PARAMETERS_TO_ELEMENTS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PARAMETERS_TO_ELEMENTS_HPP_INCLUDED

#include <sge/sprite/detail/parameters/contains_element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/fusion/at.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace parameters
{

template<
	typename Dest,
	typename Source
>
Dest const
to_elements(
	Source const &_source
)
{
	return
		Dest(
			boost::fusion::as_vector(
				boost::fusion::transform(
					boost::fusion::filter_if<
						sge::sprite::detail::parameters::contains_element<
							typename Dest::memory_type::types
						>
					>(
						boost::fusion::as_vector(
							boost::fusion::zip(
								boost::fusion::as_vector(
									typename Source::memory_type::types()
								),
								_source.memory().impl()
							)
						)
					),
					boost::phoenix::at_c<
						1
					>(
						boost::phoenix::argument<
							1
						>()
					)
				)
			)
		);
}

}
}
}
}

#endif
