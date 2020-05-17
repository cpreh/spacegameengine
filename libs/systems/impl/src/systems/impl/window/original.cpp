//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/original_window.hpp>
#include <sge/systems/impl/renderer/optional_system_ref.hpp>
#include <sge/systems/impl/renderer/system.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/systems/impl/window/original.hpp>
#include <sge/systems/impl/window/to_awl_parameters.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_ref.hpp>
#include <awl/cursor/const_optional_object_ref.hpp>
#include <awl/cursor/object.hpp>
#include <awl/cursor/optional_type.hpp>
#include <awl/cursor/type.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/visual/object.hpp>
#include <awl/window/object.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe.hpp>


sge::systems::impl::window::original::original(
	sge::systems::original_window const &_parameters,
	sge::window::system_ref const  _system,
	sge::systems::impl::renderer::optional_system_ref const &_opt_renderer_system
)
:
	sge::systems::impl::window::base(),
	awl_visual_(
		fcppt::optional::maybe(
			_opt_renderer_system,
			[
				_system
			]{
				return
					_system.get().awl_system().default_visual();
			},
			[](
				fcppt::reference<
					sge::systems::impl::renderer::system
				> const _renderer_system
			)
			{
				return
					_renderer_system.get().create_visual();
			}
		)
	),
	awl_cursor_(
		_system.get().awl_system().create_cursor(
			_parameters.hide_cursor()
			?
				awl::cursor::optional_type{}
			:
				awl::cursor::optional_type{
					awl::cursor::type::arrow
				}
		)
	),
	awl_window_(
		_system.get().awl_system().create_window(
			sge::systems::impl::window::to_awl_parameters(
				*awl_visual_,
				awl::cursor::const_optional_object_ref(
					fcppt::make_cref(
						*awl_cursor_
					)
				),
				_parameters
			)
		)
	),
	window_(
		_system,
		fcppt::make_ref(
			*awl_window_
		)
	)
{
}

sge::systems::impl::window::original::~original()
{
}

sge::window::object &
sge::systems::impl::window::original::get() const
{
	return
		window_;
}
