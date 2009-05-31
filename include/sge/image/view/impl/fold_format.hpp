/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_IMAGE_VIEW_IMPL_FOLD_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_VIEW_IMPL_FOLD_FORMAT_HPP_INCLUDED

#include <sge/image/view/impl/fold_format_operation.hpp>
#include <sge/image/view/elements.hpp>
#include <sge/image/view/const_elements.hpp>
#include <sge/image/color/format.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>

namespace sge
{
namespace image
{
namespace view
{
namespace impl 
{

template<
	typename Operation
>
typename Operation::result_type
fold_format(
	Operation const &op,
	color::format::type const fmt)
{
	typename boost::mpl::if_<
		boost::is_same<
			typename Operation::result_type,
			const_object	
		>,
		const_elements,
		elements
	>::type e;

	typename fold_format_operation<
		Operation
	>::counter_type counter(0);

	return boost::fusion::fold(
		e,
		typename Operation::result_type(),
		fold_format_operation<
			Operation
		>(
			op,
			fmt,
			counter
		)
	);
}

}
}
}
}

#endif
