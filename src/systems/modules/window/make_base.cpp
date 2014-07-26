/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/window/base_unique_ptr.hpp>
#include <sge/src/systems/modules/window/make_base.hpp>
#include <sge/src/systems/modules/window/original.hpp>
#include <sge/src/systems/modules/window/wrapped.hpp>
#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/wrapped_window_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::systems::modules::window::base_unique_ptr
sge::systems::modules::window::make_base(
	sge::systems::window const &_parameters,
	sge::window::system &_system,
	sge::systems::modules::renderer::optional_system_ref const &_renderer_system
)
{
	class visitor
	{
		FCPPT_NONASSIGNABLE(
			visitor
		);
	public:
		visitor(
			sge::window::system &_system,
			sge::systems::modules::renderer::optional_system_ref const &_renderer_system
		)
		:
			system_(
				_system
			),
			renderer_system_(
				_renderer_system
			)
		{
		}

		typedef
		sge::systems::modules::window::base_unique_ptr
		result_type;

		result_type
		operator()(
			sge::systems::original_window const &_original
		) const
		{
			return
				fcppt::make_unique_ptr<
					sge::systems::modules::window::original
				>(
					_original,
					system_,
					renderer_system_
				);
		}

		result_type
		operator()(
			sge::systems::wrapped_window const &_wrapped
		) const
		{
			return
				fcppt::make_unique_ptr<
					sge::systems::modules::window::wrapped
				>(
					_wrapped,
					system_
				);
		}
	private:
		sge::window::system &system_;

		sge::systems::modules::renderer::optional_system_ref const renderer_system_;
	};

	return
		fcppt::variant::apply_unary(
			visitor(
				_system,
				_renderer_system
			),
			_parameters.parameter()
		);
}
