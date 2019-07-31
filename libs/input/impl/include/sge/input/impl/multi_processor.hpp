//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
