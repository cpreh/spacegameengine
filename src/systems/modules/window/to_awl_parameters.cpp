/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/src/systems/modules/window/to_awl_parameters.hpp>
#include <sge/systems/original_window.hpp>
#include <awl/cursor/const_optional_object_ref_fwd.hpp>
#include <awl/cursor/object_fwd.hpp>
#include <awl/visual/object_fwd.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional/maybe_void.hpp>


awl::window::parameters
sge::systems::modules::window::to_awl_parameters(
	awl::visual::object const &_visual,
	awl::cursor::const_optional_object_ref const &_cursor,
	sge::systems::original_window const &_parameters
)
{
	awl::window::parameters result{
		_visual
	};

	result.title(
		_parameters.title().get()
	);

	fcppt::optional::maybe_void(
		_parameters.dim(),
		[
			&result
		](
			sge::window::dim const _dim
		)
		{
			result.size(
				_dim
			);
		}
	);

	fcppt::optional::maybe_void(
		_parameters.class_name(),
		[
			&result
		](
			fcppt::string const &_class_name
		)
		{
			result.class_name(
				_class_name
			);
		}
	);

	fcppt::optional::maybe_void(
		_cursor,
		[
			&result
		](
			fcppt::reference<
				awl::cursor::object const
			> const _cursor_ref
		)
		{
			result.cursor(
				_cursor_ref.get()
			);
		}
	);

	return
		result;
}
