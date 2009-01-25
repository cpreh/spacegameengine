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


#ifndef SGE_RENDERER_GLSL_UNIFORM_VALUE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_VALUE_HPP_INCLUDED

#include "int_type.hpp"
#include "float_type.hpp"
#include "uniform_vector.hpp"
#include "uniform_matrix.hpp"
#include "../../array_wrapper.hpp"
#include <sge/math/matrix/basic_impl.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/variant/variant.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{

namespace detail
{

typedef boost::mpl::vector<
	int_type,
	float_type,
	uniform_vector,
	uniform_matrix
> uniform_base_values;

template<
	typename T
> struct make_array_wrapper {
	typedef array_wrapper<
		T
	> type;
};

}

typedef boost::make_variant_over<
	boost::mpl::copy<
		detail::uniform_base_values,
		boost::mpl::back_inserter<
			boost::mpl::transform<
				detail::uniform_base_values,
				detail::make_array_wrapper<
					boost::mpl::_1
				>
			>::type
		>
	>::type
>::type uniform_value;

}
}
}

#endif
