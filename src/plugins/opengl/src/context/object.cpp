/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/optional_base_ref.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::context::object::object(
	sge::opengl::info::context const &_info
)
:
	info_(
		_info
	),
	elements_()
{
}

sge::opengl::context::object::~object()
{
}

sge::opengl::context::optional_base_ref
sge::opengl::context::object::get(
	sge::opengl::context::id const _id
)
{
	return
		fcppt::optional::deref(
			elements_[
				_id.get()
			]
		);
}

sge::opengl::context::base &
sge::opengl::context::object::insert(
	sge::opengl::context::id const _id,
	sge::opengl::context::base_unique_ptr &&_ptr
)
{
	optional_base_unique_ptr &dest(
		elements_[
			_id.get()
		]
	);

	FCPPT_ASSERT_PRE(
		!dest.has_value()
	);

	sge::opengl::context::base &result(
		*_ptr
	);

	dest =
		optional_base_unique_ptr(
			std::move(
				_ptr
			)
		);

	return
		result;
}

sge::opengl::info::context const &
sge::opengl::context::object::info() const
{
	return
		info_;
}
