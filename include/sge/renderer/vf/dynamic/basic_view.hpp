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


#ifndef SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vf/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

template<
	typename Pointer
>
class basic_view
{
	FCPPT_NONASSIGNABLE(
		basic_view
	);
public:
	typedef Pointer pointer;

	typedef renderer::vertex_count size_type;

	SGE_RENDERER_SYMBOL
	basic_view(
		pointer data,
		size_type elements,
		dynamic::part const &,
		dynamic::part_index
	);

	SGE_RENDERER_SYMBOL
	pointer
	data() const;

	SGE_RENDERER_SYMBOL
	size_type
	size() const;

	SGE_RENDERER_SYMBOL
	dynamic::part const &
	part() const;

	SGE_RENDERER_SYMBOL
	dynamic::part_index const
	part_index() const;
private:
	pointer const data_;

	size_type const size_;

	dynamic::part const &part_;

	dynamic::part_index const part_index_;
};

}
}
}
}

#endif
