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


#ifndef SGE_INPUT_IMPL_MULTI_PROCESSOR_HPP_INCLUDED
#define SGE_INPUT_IMPL_MULTI_PROCESSOR_HPP_INCLUDED

#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/impl/system_ptr_vector.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/function_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{
namespace impl
{

class multi_processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		multi_processor
	);
public:
	multi_processor(
		fcppt::log::object &,
		sge::window::object &,
		sge::input::impl::system_ptr_vector const &
	);

	~multi_processor()
	override;
private:
	sge::window::object &
	window() const
	override;

	sge::input::cursor::container
	cursors() const
	override;

	sge::input::focus::container
	foci() const
	override;

	sge::input::joypad::container
	joypads() const
	override;

	sge::input::keyboard::container
	keyboards() const
	override;

	sge::input::mouse::container
	mice() const
	override;

	template<
		typename Container
	>
	using
	collect_function
	=
	fcppt::function<
		Container (
			sge::input::processor const &
		)
	>;

	template<
		typename Container
	>
	Container
	collect(
		collect_function<
			Container
		> const &
	) const;

	sge::window::object &window_;

	typedef
	std::vector<
		sge::input::processor_unique_ptr
	>
	processor_vector;

	processor_vector const processors_;
};

}
}
}

#endif
