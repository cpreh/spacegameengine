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


#ifndef SGE_RENDERER_VF_MAKE_DYNAMIC_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_MAKE_DYNAMIC_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic_element_list.hpp>
#include <sge/renderer/vf/dynamic_offset_list.hpp>
#include <sge/renderer/vf/make_dynamic_elements.hpp>
#include <sge/renderer/vf/make_dynamic_offsets.hpp>
#include <sge/renderer/vf/dynamic_format.hpp>
#include <boost/mpl/for_each.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<typename Format>
dynamic_format const
make_dynamic_format()
{
	typedef typename Format::elements elements;
	typedef typename Format::offsets offsets;

	dynamic_element_list elems;
	boost::mpl::for_each<
		elements>(
			make_dynamic_elements(
				elems));

	dynamic_offset_list offs;
	boost::mpl::for_each<
		offsets>(
			make_dynamic_offsets(
				offs));

	return dynamic_format(
		elems,
		offs);
}

}
}
}

#endif
