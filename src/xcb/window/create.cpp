/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "convert_class.hpp"
#include <sge/xcb/window/create.hpp>
#include <sge/xcb/window/object.hpp>
#include <sge/xcb/window/attribute/list.hpp>
#include <sge/xcb/connection.hpp>
#include <sge/xcb/create_id.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sge::xcb::window::unique_ptr
sge::xcb::window::create(
	connection const &connection_,
	id_num const &parent_,
	pos const &pos_,
	dim const &dim_,
	depth const &depth_,
	border_width const &border_width_,
	class_::type const class_value_,
	visual::id_num const &visual_id_,
	attribute::list const &attributes_
)
{
	id_num const window_num(
		create_id(
			connection_
		)
	);

	xcb_create_window(
		connection_.get(),
		depth_,
		window_num,
		parent_,
		pos_.x(),
		pos_.y(),
		dim_.w(),
		dim_.h(),
		border_width_,
		convert_class(
			class_value_
		),
		visual_id_,
		attributes_.value_mask(),
		attributes_.data()
	);

	return
		fcppt::make_unique_ptr<
			window::object
		>(
			window_num,
			connection_
		);
}
