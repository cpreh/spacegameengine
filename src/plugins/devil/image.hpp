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


#ifndef SGE_DEVIL_IMAGE_HPP_INCLUDED
#define SGE_DEVIL_IMAGE_HPP_INCLUDED

#include "../../image/image.hpp"
#include "../../shared_ptr.hpp"
#include "../../auto_ptr.hpp"
#include <IL/il.h>

namespace sge
{
namespace devil
{

class image : public sge::image {
public:
	image(const std::string& file);
	image(const_pointer p, size_type w, size_type h);
	const_pointer data() const;
	void data(const_pointer);
	size_type width() const;
	size_type height() const;
	void resample(size_type w, size_type h);
	void save(const std::string& path);
private:
	void init();
	void bind_me() const;
	struct im_guard {
		im_guard(ILuint i) : i(i) {}
		~im_guard() { ilDeleteImages(1,&i); }
		operator ILuint() const { return i; }
	private:
		ILuint i;
	};
	typedef auto_ptr<im_guard> im_guard_ptr;
	im_guard_ptr id;
	size_type w, h;
};

typedef shared_ptr<image> image_ptr;

}
}

#endif

