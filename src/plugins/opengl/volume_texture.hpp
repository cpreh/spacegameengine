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


#ifndef SGE_OPENGL_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_VOLUME_TEXTURE_HPP_INCLUDED

#include "common.hpp"
#include "basic_texture.hpp"
#include <sge/renderer/volume_texture.hpp>

namespace sge
{
namespace ogl
{

namespace detail
{

typedef basic_texture<renderer::volume_texture> volume_texture_base;

}

class volume_texture : public detail::volume_texture_base {
public:
	volume_texture(
		image_view_array const &,
		const renderer::filter_args& filter,
		resource_flag_type flags);

	const box_type box() const;

	void data(
		image_view_array const&);
	void sub_data(
		image_view_array const&,
		const renderer::lock_box& b);

	const image_view_array data() const;

	void lock();
	void lock(renderer::lock_box const &);
	void unlock();
private:
	const box_type box_;
};

}
}

#endif
