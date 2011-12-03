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


#ifndef SGE_CAMERA_PROJECTION_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_OBJECT_HPP_INCLUDED

#include <sge/camera/projection/orthogonal.hpp>
#include <sge/camera/projection/invalid.hpp>
#include <sge/camera/projection/perspective.hpp>
#include <fcppt/variant/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace camera
{
namespace projection
{
typedef
fcppt::variant::object
<
	boost::mpl::vector3
	<
		projection::orthogonal,
		projection::perspective,
		projection::invalid
	>
>
object;
}
}
}

#endif
