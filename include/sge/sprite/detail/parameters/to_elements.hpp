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

#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/contains.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace parameters
{

// TODO: Clean this up!
struct at_impl
{
	template<
		typename
	>
	struct result;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)
	template<
		typename Container
	>
	struct result<
		at_impl(
			Container
		)
	>
	:
	std::remove_reference<
		typename boost::fusion::result_of::at_c<
			typename std::remove_const<
				typename std::remove_reference<
					Container
				>::type
			>::type,
			1u
		>::type
	>
	{
	};
FCPPT_PP_POP_WARNING

	template<
		typename Container
	>
	typename
	result<
		at_impl(
			Container
		)
	>::type
	operator()(
		Container const &_container
	) const
	{
		return
			boost::fusion::at_c<
				1u
			>(
				_container
			);
	}
};

template<
	typename Dest
>
struct my_contains
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)
        template<
                typename Elem
        >
        struct apply
        :
        boost::mpl::contains<
                Dest,
                typename boost::mpl::at_c<
			Elem,
			0
		>::type
	>
	{
	};
FCPPT_PP_POP_WARNING
};

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
						my_contains<
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
					at_impl()
				)
			)
		);
}

}
}
}
}

#endif
