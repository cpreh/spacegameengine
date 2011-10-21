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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_PART_LIST_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_PART_LIST_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/vf/dynamic/detail/make_part.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

class make_part_list
{
	FCPPT_NONASSIGNABLE(
		make_part_list
	);
public:
	explicit make_part_list(
		part_list &_parts
	)
	:
		parts_(_parts)
	{
	}

	typedef void result_type;

	template<
		typename Type
	>
	result_type
	operator()(
		Type const &
	) const
	{
		parts_.push_back(
			detail::make_part<
				Type
			>()
		);
	}
private:
	part_list &parts_;
};

}
}
}
}
}

#endif
