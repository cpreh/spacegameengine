/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_VOLUME_TEXTURE_HPP_INCLUDED

#include "basic_texture.hpp"
#include "context/object_fwd.hpp"
#include <sge/image/color/format.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/volume_texture.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/filter/texture_fwd.hpp>
#include <fcppt/math/box/basic_decl.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>

namespace sge
{
namespace opengl
{

namespace detail
{
typedef basic_texture<
	renderer::volume_texture
> volume_texture_base;
}

class volume_texture
:
	public detail::volume_texture_base
{
	FCPPT_NONCOPYABLE(
		volume_texture
	)
public:
	volume_texture(
		opengl::context::object &,
		dim_type const &,
		sge::image::color::format::type,
		sge::renderer::filter::texture const &,
		sge::renderer::resource_flags_field const &
	);

	~volume_texture();

	dim_type const
	dim() const;

	image3d::view::object const
	lock(
		box_type const &,
		renderer::lock_mode::type
	);

	image3d::view::const_object const
	lock(
		box_type const &
	) const;

	void
	unlock() const;
private:
	void
	lock_me(
		box_type const &,
		lock_method::type
	) const;

	image3d::view::object const
	view();

	image3d::view::const_object const
	view() const;

	dim_type const
	lock_dim() const;

	dim_type const dim_;

	mutable fcppt::optional<
		box_type
	> lock_rect_;
};

}
}

#endif
