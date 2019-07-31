//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/impl/multi_processor.hpp>
#include <sge/input/impl/system_ptr_vector.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/bad_dynamic.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::input::impl::multi_processor::multi_processor(
	fcppt::log::object &_log,
	sge::window::object &_window,
	sge::input::impl::system_ptr_vector const &_systems
)
:
	sge::input::processor(),
	window_{
		_window
	},
	processors_(
		fcppt::algorithm::map_optional<
			sge::input::impl::multi_processor::processor_vector
		>(
			_systems,
			[
				&_log,
				&_window
			](
				sge::input::system_unique_ptr const &_system
			)
			{
				typedef
				fcppt::optional::object<
					sge::input::processor_unique_ptr
				>
				optional_processor;

				try
				{
					return
						optional_processor{
							_system->create_processor(
								_window
							)
						};
				}
				catch(
					fcppt::cast::bad_dynamic const &_error
				)
				{
					FCPPT_LOG_WARNING(
						_log,
						fcppt::log::out
							<<
							FCPPT_TEXT("Unusable input plugin: ")
							<<
							_error.string()
					)

					return
						optional_processor{};
				}
			}
		)
	)
{
}

sge::input::impl::multi_processor::~multi_processor()
{
}

sge::window::object &
sge::input::impl::multi_processor::window() const
{
	return
		window_;
}

sge::input::cursor::container
sge::input::impl::multi_processor::cursors() const
{
	return
		this->collect(
			collect_function<
				sge::input::cursor::container
			>(
				std::bind(
					&sge::input::processor::cursors,
					std::placeholders::_1
				)
			)
		);
}

sge::input::focus::container
sge::input::impl::multi_processor::foci() const
{
	return
		this->collect(
			collect_function<
				sge::input::focus::container
			>(
				std::bind(
					&sge::input::processor::foci,
					std::placeholders::_1
				)
			)
		);
}

sge::input::joypad::container
sge::input::impl::multi_processor::joypads() const
{
	return
		this->collect(
			collect_function<
				sge::input::joypad::container
			>(
				std::bind(
					&sge::input::processor::joypads,
					std::placeholders::_1
				)
			)
		);
}

sge::input::keyboard::container
sge::input::impl::multi_processor::keyboards() const
{
	return
		this->collect(
			collect_function<
				sge::input::keyboard::container
			>(
				std::bind(
					&sge::input::processor::keyboards,
					std::placeholders::_1
				)
			)
		);
}

sge::input::mouse::container
sge::input::impl::multi_processor::mice() const
{
	return
		this->collect(
			collect_function<
				sge::input::mouse::container
			>(
				std::bind(
					&sge::input::processor::mice,
					std::placeholders::_1
				)
			)
		);
}

template<
	typename Container
>
Container
sge::input::impl::multi_processor::collect(
	collect_function<
		Container
	> const &_function
) const
{
	return
		fcppt::algorithm::map_concat<
			Container
		>(
			processors_,
			[
				&_function
			](
				sge::input::processor_unique_ptr const &_processor
			)
			{
				return
					_function(
						*_processor
					);
			}
		);
}
