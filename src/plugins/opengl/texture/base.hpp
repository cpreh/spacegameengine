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


#ifndef SGE_OPENGL_TEXTURE_BASE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "holder.hpp"
#include "id.hpp"
#include "type.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
public:
	texture::type const
	type() const;

	texture::id const
	id() const;

	bool
	update_filter(
		renderer::texture::filter::object const &
	) const;

	bool
	has_mipmap() const;

	virtual ~base();
protected:
	explicit base(
		texture::type
	);
private:
	virtual renderer::texture::mipmap::object const
	mipmap() const = 0;

	texture::type const type_;

	opengl::texture::holder const holder_;

	mutable sge::renderer::texture::filter::object filter_;
};

}
}
}

#endif
