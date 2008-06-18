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


#ifndef SGE_RENDERER_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_CUBE_TEXTURE_HPP_INCLUDED

#include "../export.hpp"
#include "image_view.hpp"
#include "texture_base.hpp"
#include "types.hpp"
#include <boost/array.hpp>

namespace sge
{
namespace renderer
{

namespace cube_side
{
	enum type {
		front,
		back,
		left,
		right,
		top,
		bottom,
		num_elements
	};
}

class cube_texture : public texture_base {
public:
	typedef boost::array<image_view, cube_side::num_elements> image_view_6;

	virtual void data(
		cube_side::type side,
		image_view const &) = 0;
	void sub_data(
		cube_side::type side,
		const_image_view const &,
		lock_rect const &dest);
	virtual void lock(
		cube_side::type side,
		lock_flag_type) = 0;
	virtual void lock(
		cube_side::type side,
		lock_rect const &,
		lock_flag_type) = 0;
	virtual void unlock() = 0;

	size_type size() const;
	virtual image_view const view() = 0;
	virtual const_image_view const view() const = 0;
	virtual size_type border_size() const = 0;
private:
	virtual void do_sub_data(
		cube_side::type side,
		const_image_view const &,
		lock_rect const &dest) = 0;
};

typedef shared_ptr<cube_texture> cube_texture_ptr;

}
}

#endif
