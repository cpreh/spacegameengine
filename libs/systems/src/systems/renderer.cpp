//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/name.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::systems::renderer::renderer(
	sge::renderer::pixel_format::object const &_pixel_format,
	sge::renderer::display_mode::parameters const _display_mode,
	sge::viewport::optional_resize_callback &&_resize_callback
)
:
	pixel_format_(
		_pixel_format
	),
	display_mode_(
		_display_mode
	),
	resize_callback_(
		std::move(
			_resize_callback
		)
	),
	caps_(
		sge::renderer::caps::system_field::null()
	),
	name_()
{
}

sge::systems::renderer
sge::systems::renderer::caps(
	sge::renderer::caps::system_field const &_caps
) &&
{
	caps_ =
		_caps;

	return
		std::move(
			*this
		);
}

sge::systems::renderer
sge::systems::renderer::name(
	sge::plugin::name &&_name
) &&
{
	name_ =
		sge::systems::optional_name(
			std::move(
				_name
			)
		);

	return
		std::move(
			*this
		);
}

sge::renderer::pixel_format::object const &
sge::systems::renderer::pixel_format() const
{
	return
		pixel_format_;
}

sge::renderer::display_mode::parameters const &
sge::systems::renderer::display_mode() const
{
	return
		display_mode_;
}

sge::viewport::optional_resize_callback const &
sge::systems::renderer::resize_callback() const
{
	return
		resize_callback_;
}

sge::renderer::caps::system_field const &
sge::systems::renderer::caps() const
{
	return
		caps_;
}

sge::systems::optional_name const &
sge::systems::renderer::name() const
{
	return
		name_;
}
