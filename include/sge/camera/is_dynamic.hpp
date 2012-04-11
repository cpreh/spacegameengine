/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CAMERA_IS_DYNAMIC_HPP_INCLUDED
#define SGE_CAMERA_IS_DYNAMIC_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL is_dynamic
:
	public virtual camera::base
{
FCPPT_NONCOPYABLE(
	is_dynamic);
protected:
	SGE_CAMERA_SYMBOL
	explicit
	is_dynamic();
public:
	virtual void
	update(
		camera::update_duration const &) = 0;

	SGE_CAMERA_SYMBOL
	virtual ~is_dynamic() = 0;
};
}
}

#endif

