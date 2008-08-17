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


#ifndef SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED

#include "index_format.hpp"
#include "../typeswitch.hpp"
#include "../export.hpp"
#include <boost/variant.hpp>
#include <cstddef>

namespace sge
{
namespace renderer
{

typedef std::size_t index_size;

template<typename Index>
class index_view {
public:
	typedef index_size size_type;
	typedef Index value_type;
	typedef value_type *pointer;
	typedef pointer iterator;

	SGE_SYMBOL index_view(
		pointer,
		size_type);

	SGE_SYMBOL pointer data() const;
	SGE_SYMBOL size_type size() const;

	SGE_SYMBOL iterator begin() const;
	SGE_SYMBOL iterator end() const;

	SGE_SYMBOL index_format::type format() const;
private:
	pointer data_;
	size_type size_;
};

typedef index_view<uint16> index_view_16;
typedef index_view<uint16 const> const_index_view_16;
typedef index_view<uint32> index_view_32;
typedef index_view<uint32 const> const_index_view_32;

// FIXME: we should really use a variant with an mpl::vector here
// so that return types of visitor algorithms can be deduced
typedef boost::variant<
	index_view_16,
	index_view_32
> dynamic_index_view;

typedef boost::variant<
	const_index_view_16,
	const_index_view_32
> const_dynamic_index_view;

}
}

#endif
