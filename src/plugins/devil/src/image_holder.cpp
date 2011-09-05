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


#include "../image_holder.hpp"
#include "../check_error_exn.hpp"
#include <fcppt/config/external_begin.hpp>
#include <IL/il.h>
#include <fcppt/config/external_end.hpp>

sge::devil::image_holder::image_holder()
{
	::ilGenImages(
		1,
		&id_
	);

	devil::check_error_exn();
}

sge::devil::image_holder::~image_holder()
{
	::ilDeleteImages(
		1,
		&id_
	);
}

ILuint
sge::devil::image_holder::id() const
{
	return id_;
}
