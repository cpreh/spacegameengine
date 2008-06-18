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
#include <sge/renderer/texture.hpp>
#include <sge/renderer/image.hpp>

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
	texture(
		renderer::const_image_view const &src,
		renderer::filter_args const &filter,
		resource_flag_type flags);

	const dim_type dim() const;

	void data(
		renderer::const_image_view const &src);
	void sub_data(
		renderer::const_image_view const &src,
		renderer::lock_rect const &r);

	void lock(
		lock_flag_type flags);
	void lock(
		renderer::lock_rect const &,
		lock_flag_type flags);
	void unlock();
private:
	void data_internal(
		renderer::const_image_view const &src);
	void allocate_texture(
		renderer::const_image_view const &src);

	void set_texture(const_pointer src);

	dim_type dim_;
};

}
}

#endif

