/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../object.hpp"
#include "../base.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <utility>

sge::opengl::context::object::object()
:
	elements_()
{}

sge::opengl::context::object::~object()
{
}

sge::opengl::context::base *
sge::opengl::context::object::get(
	context::id const id_
)
{
	container::iterator const it(
		elements_.find(
			id_
		)
	);

	return
		it == elements_.end()
		?
			static_cast<base *>(0)
		:
			it->second;
}

sge::opengl::context::base &
sge::opengl::context::object::insert(
	context::id const id_,
	base_auto_ptr ptr_
)
{
	typedef std::pair<
		container::iterator,
		bool
	> ret_type;

	ret_type const ret(
		elements_.insert(
			id_,
			ptr_
		)
	);

	if(
		!ret.second
	)
		throw sge::exception(
			FCPPT_TEXT("Double insert in opengl::context!")
		);
	
	return *ret.first->second;
}
