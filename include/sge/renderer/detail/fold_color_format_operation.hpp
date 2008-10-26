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


#ifndef SGE_RENDERER_DETAIL_FOLD_COLOR_FORMAT_OPERATION_HPP_INCLUDED
#define SGE_RENDERER_DETAIL_FOLD_COLOR_FORMAT_OPERATION_HPP_INCLUDED

#include "../color_format.hpp"

namespace sge
{
namespace renderer
{

template<
	typename Operation
>
class fold_color_format_operation {
	typedef unsigned long counter_type;
public:
	typedef typename Operation::result_type result_type;

	explicit fold_color_format_operation(
		Operation const &op,
		color_format::type const fmt)
	:
		op(op),
		fmt(fmt),
		count(0)
	{}

	template<typename T>
	result_type const operator()(
		T const &,
		result_type const &v) const
	{
		return count++ == static_cast<counter_type>(fmt)
		? op.operator()<T>()
		: v;
	}
private:
	Operation const op;
	color_format::type const fmt;
	mutable counter_type count;
};

}
}

#endif
