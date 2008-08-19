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


#ifndef SGE_OPENGL_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_HPP_INCLUDED

#include "common.hpp"
#include "basic_texture.hpp"
#include "lock_method.hpp"
#include <sge/renderer/texture.hpp>
#include <sge/renderer/image.hpp>
#include <sge/renderer/color_format.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace ogl
{

namespace detail
{
typedef basic_texture<renderer::texture> texture_base;
}

class texture : public detail::texture_base {
public:
	typedef boost::optional<GLenum> optional_type;

	texture(
		dim_type const &,
		renderer::color_format::type format,
		renderer::filter_args const &filter,
		resource_flag_type flags,
		optional_type type
			= optional_type());
	
	dim_type const dim() const;
	
	renderer::image_view const lock(
		renderer::lock_rect const &,
		lock_flag_type flags);

	renderer::const_image_view const lock(
		renderer::lock_rect const &) const;

	void unlock() const;
private:
	void lock_me(
		renderer::lock_rect const &,
		lock_method::type) const;

	renderer::image_view const view();
	renderer::const_image_view const view() const;

	dim_type const lock_dim() const;
	
	void set_texture(
		const_pointer src) const;

	dim_type const               dim_;
	mutable boost::optional<
		renderer::lock_rect> lock_rect_;
};

}
}

#endif

