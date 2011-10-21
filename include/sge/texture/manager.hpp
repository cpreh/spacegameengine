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


#ifndef SGE_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_TEXTURE_MANAGER_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/manager_fwd.hpp>
#include <sge/texture/on_alloc_function.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/symbol.hpp>
#include <sge/texture/detail/container_position.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	SGE_TEXTURE_SYMBOL
	explicit manager(
		texture::on_alloc_function const &
	);

	SGE_TEXTURE_SYMBOL
	~manager();

	SGE_TEXTURE_SYMBOL
	texture::part_ptr const
	add(
		image2d::view::const_object const &
	);

	SGE_TEXTURE_SYMBOL
	void
	on_alloc(
		texture::on_alloc_function const &
	);

	SGE_TEXTURE_SYMBOL
	void
	free_empty_textures();
private:
	friend class fragmented;

	void
	part_freed(
		detail::container_position const &,
		fragmented const &
	);

	on_alloc_function on_alloc_;

	detail::fragmented_queue free_textures_;

	detail::fragmented_list full_textures_;
};

}
}

#endif
