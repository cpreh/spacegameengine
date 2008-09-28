/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_FORMAT_HPP_INCLUDED

#include "../../partial_sums.hpp"
#include "raw_pointer.hpp"
#include "element_stride.hpp"
#include <boost/mpl/transform.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename ElementList,
	bool IsConst = false // FIXME!
>
struct format {
	typedef ElementList elements;

	typedef typename boost::mpl::transform<
		elements,
		element_stride<
			boost::mpl::_1
		>
	>::type strides;

	typedef typename partial_sums<
		strides
	>::type offsets;

	typedef typename boost::mpl::if_c<
		IsConst,
		const_raw_pointer,
		raw_pointer
	>::type pointer;
};

}
}
}

#endif
