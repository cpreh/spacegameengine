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


#include <sge/opengl/logger.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/container.hpp>
#include <sge/opengl/context/optional_base_ref.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_assign.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_deref.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::context::container::container()
:
	elements_(
		// TODO: Can we read the current count?
		50u
	)
{
}

sge::opengl::context::container::~container()
{
}

sge::opengl::context::optional_base_ref
sge::opengl::context::container::get(
	size_type const _index
) const
{
	return
		fcppt::optional_bind(
			fcppt::container::at_optional(
				elements_,
				_index
			),
			[](
				optional_unique_ptr const &_element
			)
			{
				return
					fcppt::optional_deref(
						_element
					);
			}
		);
}

sge::opengl::context::optional_base_ref
sge::opengl::context::container::insert(
	size_type const _index,
	sge::opengl::context::base_unique_ptr &&_ptr
)
{
	// TODO: Can be improve this?
	if(
		_index
		>=
		elements_.size()
	)
		elements_.resize(
			_index
			+
			1u
		);

	optional_unique_ptr &element(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::at_optional(
				elements_,
				_index
			)
		)
	);

	return
		fcppt::maybe(
			element,
			[
				&element,
				&_ptr
			]{
				return
					sge::opengl::context::optional_base_ref(
						*fcppt::optional_assign(
							element,
							std::move(
								_ptr
							)
						)
					);
			},
			[](
				sge::opengl::context::base_unique_ptr const &
			)
			{
				return
					sge::opengl::context::optional_base_ref();
			}
		);
}
