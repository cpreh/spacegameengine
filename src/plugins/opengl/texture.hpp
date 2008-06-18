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
		const_pointer src,
		const dim_type& dim,
		const renderer::filter_args& filter,
		resource_flag_type flags);

	const dim_type dim() const;

	void set_data(const_pointer src, const renderer::lock_rect& r);
	void set_data(const_pointer src);

	void lock(lock_flag_type flags);
	void lock(const renderer::lock_rect&, lock_flag_type flags);
	void unlock();
private:
	void set_texture(const_pointer src);

	const dim_type dim_;
};

}
}

#endif

