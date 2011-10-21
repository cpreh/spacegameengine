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


#ifndef SGE_CAMERA_BASE_HPP_INCLUDED
#define SGE_CAMERA_BASE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/duration.hpp>
#include <sge/camera/gizmo_type.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>


namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(
	base);
protected:
	SGE_CAMERA_SYMBOL explicit
	base(
		camera::projection::object const &,
		camera::gizmo_type const &);

public:
	virtual void
	update(
		camera::duration const &) = 0;

	virtual bool
	active() const = 0;

	virtual void
	active(
		bool) = 0;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	world() const;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	rotation() const;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	translation() const;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	projection() const;

	SGE_CAMERA_SYMBOL
	projection::object const
	projection_object() const;

	SGE_CAMERA_SYMBOL
	void
	projection_object(
		projection::object const &);

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	mvp() const;

	SGE_CAMERA_SYMBOL
	camera::gizmo_type const &
	gizmo() const;

	SGE_CAMERA_SYMBOL
	camera::gizmo_type &
	gizmo();

	SGE_CAMERA_SYMBOL virtual ~base() = 0;
private:
	projection::object projection_object_;
	renderer::matrix4 projection_matrix_;
	// The camera's position and orientation
	camera::gizmo_type gizmo_;
	bool active_;
};
}
}

#endif
