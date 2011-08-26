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


#ifndef SGE_MODEL_MD3_TAG_HPP_INCLUDED
#define SGE_MODEL_MD3_TAG_HPP_INCLUDED

#include "axis_array.hpp"
#include "vec3.hpp"
#include <sge/model/md3/string.hpp>
#include <fcppt/container/array_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <iosfwd>

namespace sge
{
namespace model
{
namespace md3
{

class tag
{
public:
	explicit tag(
		std::istream &
	);

	md3::string const &
	name() const;

	md3::vec3 const &
	origin() const;

	md3::axis_array const &
	axis() const;
private:
	md3::string name_;

	md3::vec3 origin_;

	md3::axis_array axis_;
};

}
}
}

#endif
