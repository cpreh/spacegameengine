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


#ifndef SGE_RENDERER_VF_RAW_DATA_HPP_INCLUDED
#define SGE_RENDERER_VF_RAW_DATA_HPP_INCLUDED

#include <sge/renderer/vf/raw_pointer.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <boost/gil/pixel.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<typename T>
const_raw_pointer
raw_data(
	T const &t);

template<
	typename T,
	typename N,
	typename S
>
const_raw_pointer
raw_data(
	math::vector::basic<T, N, S> const &v)
{
	return reinterpret_cast<const_raw_pointer>(v.data());
}

template<typename Channel, typename Layout>
const_raw_pointer
raw_data(
	boost::gil::pixel<Channel, Layout> const &t)
{
	return reinterpret_cast<const_raw_pointer>(&t); // FIXME
}

}
}
}

#endif
