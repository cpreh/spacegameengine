/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_TEXTURE_MANAGER_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include "../shared_ptr.hpp"
#include "../exception.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/texture.hpp"
#include "fragmented_texture.hpp"

namespace sge
{

class texture_manager : boost::noncopyable {
public:
	texture_manager(renderer_ptr rend, fragmented_texture_ptr proto);
	const virtual_texture_ptr add_texture(texture::const_pointer src, texture::size_type w, texture::size_type h);
	const virtual_texture_ptr add_texture(texture_ptr tex);
	const renderer_ptr get_renderer() const;
	void prototype(fragmented_texture_ptr);

	class image_too_big : public exception {
	public:
		image_too_big();
	};
private:
	const renderer_ptr                          rend;
	fragmented_texture_ptr                      _prototype;
	typedef boost::ptr_list<fragmented_texture> fragmented_texture_list;
	fragmented_texture_list                     fragmented_textures;
};

typedef shared_ptr<texture_manager> texture_manager_ptr;

}

#endif
