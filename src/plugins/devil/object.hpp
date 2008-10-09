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


#ifndef SGE_DEVIL_OBJECT_HPP_INCLUDED
#define SGE_DEVIL_OBJECT_HPP_INCLUDED

#include "image_impl.hpp"
#include <sge/path.hpp>
#include <sge/image/object.hpp>
#include <sge/image/format.hpp>

namespace sge
{
namespace devil
{

class object : public image::object {
public:
	explicit object(
		path const &);
	/*object(
		image::format::type type,
		const_pointer format_data,
		size_type size);*/
	explicit object(
		renderer::const_image_view const &);
	renderer::const_image_view const view() const;
	void data(
		renderer::const_image_view const &);
	const dim_type dim() const;
	void resample(dim_type const &);
	void save(path const &);
private:
	void bind_me() const;
	image_impl impl;
};

}
}

#endif

