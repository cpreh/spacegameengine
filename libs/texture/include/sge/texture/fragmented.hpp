/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/optional_part_unique_ptr_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL fragmented
{
	FCPPT_NONCOPYABLE(
		fragmented
	);
protected:
	SGE_TEXTURE_DETAIL_SYMBOL
	fragmented();
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	virtual
	~fragmented();

	virtual
	sge::texture::optional_part_unique_ptr
	consume_fragment(
		sge::renderer::dim2 const &
	) = 0;

	virtual
	void
	return_fragment(
		sge::texture::part const &
	) = 0;

	virtual
	sge::renderer::texture::planar &
	texture() = 0;

	virtual
	sge::renderer::texture::planar const &
	texture() const = 0;

	virtual
	bool
	repeatable() const = 0;

	virtual
	bool
	empty() const = 0;
};

}
}

#endif
