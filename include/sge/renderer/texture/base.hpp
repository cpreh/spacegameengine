/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	base();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~base() = 0;

	virtual
	sge::renderer::resource_flags_field
	resource_flags() const = 0;

	virtual
	sge::renderer::texture::capabilities_field
	capabilities() const = 0;

	virtual
	sge::renderer::texture::mipmap::object
	mipmap() const = 0;

	virtual
	sge::renderer::texture::mipmap::level_count
	levels() const = 0;

	virtual
	void
	generate_mipmaps() = 0;
};

}
}
}

#endif
