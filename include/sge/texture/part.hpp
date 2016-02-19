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


#ifndef SGE_TEXTURE_PART_HPP_INCLUDED
#define SGE_TEXTURE_PART_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL part
{
	FCPPT_NONCOPYABLE(
		part
	);
protected:
	SGE_TEXTURE_DETAIL_SYMBOL
	part();
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	virtual
	~part() = 0;

	virtual
	void
	data(
		sge::image2d::view::const_object const &,
		sge::image::algorithm::uninitialized
	) = 0;

	virtual
	sge::renderer::lock_rect
	area() const = 0;

	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::dim2
	size() const;

	virtual
	sge::renderer::texture::planar &
	texture() const = 0;

	virtual
	bool
	repeatable() const = 0;
};

}
}

#endif
