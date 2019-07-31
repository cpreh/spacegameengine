//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/original_window.hpp>
#include <sge/systems/impl/window/to_awl_parameters.hpp>
#include <awl/cursor/const_optional_object_ref_fwd.hpp>
#include <awl/cursor/object_fwd.hpp>
#include <awl/visual/object_fwd.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional/maybe_void.hpp>


awl::window::parameters
sge::systems::impl::window::to_awl_parameters(
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
