/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_PROJECTION_RECTANGLE_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PROJECTION_RECTANGLE_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/object_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
class projection_rectangle_from_viewport
{
FCPPT_NONCOPYABLE(
	projection_rectangle_from_viewport);
public:
	SGE_CAMERA_SYMBOL
	projection_rectangle_from_viewport(
		sge::camera::ortho_freelook::object &,
		sge::viewport::manager &);

	SGE_CAMERA_SYMBOL
	~projection_rectangle_from_viewport();
private:
	sge::camera::ortho_freelook::object &camera_;
	fcppt::signal::scoped_connection viewport_callback_connection_;

	void
	viewport_callback(
		sge::renderer::target::viewport const &);
};
}
}
}

#endif
