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

#include <sge/renderer/vf/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/symbol.hpp>
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
	typedef Pointer     pointer;
	typedef vertex_size size_type;

	SGE_SYMBOL basic_view(
		pointer data,
		size_type elements,
		dynamic::format const &
	);

	SGE_SYMBOL pointer
	data() const;

	SGE_SYMBOL size_type
	size() const;

	SGE_SYMBOL dynamic::format const &
	format() const;
private:
	pointer data_;

	size_type size_;

	dynamic::format const &format_;
};

}
}
}
}

#endif
