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


#include <sge/model/obj/instance_ptr.hpp>
#include <sge/src/model/obj/instance_impl.hpp>
#include <sge/src/model/obj/loader_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/filesystem/path.hpp>


sge::model::obj::loader_impl::loader_impl()
:
	tokens_()
{
}

sge::model::obj::loader_impl::~loader_impl()
{
}

sge::model::obj::instance_ptr const
sge::model::obj::loader_impl::load(
	fcppt::filesystem::path const &_path
)
{
	return
		fcppt::make_shared_ptr<
			obj::instance_impl
		>(
			fcppt::cref(
				tokens_
			),
			_path
		);
}
