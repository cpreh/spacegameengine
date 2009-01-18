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


#ifndef SGE_IMAGE_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_OBJECT_HPP_INCLUDED

#include "../export.hpp"
#include "../filesystem/path.hpp"
#include "../renderer/image_view.hpp"
#include <sge/math/dim/static.hpp>
#include <sge/math/dim/basic_decl.hpp>
#include <boost/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace image
{

class SGE_CLASS_SYMBOL object : boost::noncopyable {
public:
	typedef std::size_t size_type;

	typedef math::dim::static_<
		size_type,
		2
	>::type dim_type;

	virtual void data(
		renderer::const_image_view const &) = 0;
	virtual renderer::const_image_view const view() const = 0;
	virtual dim_type const dim() const = 0;
	virtual void resample(dim_type const &) = 0;
	virtual void save(filesystem::path const &) = 0;
	SGE_SYMBOL virtual ~object();
};

}
}

#endif
