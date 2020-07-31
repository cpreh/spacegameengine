//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_DEMUXER_IMPL_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_DEMUXER_IMPL_HPP_INCLUDED

#include <sge/window/event_combiner.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/demuxer_decl.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/unregister/base_impl.hpp>
#include <fcppt/signal/unregister/function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Event
>
sge::x11input::event::demuxer<
	Event
>::demuxer(
	awl::backends::x11::window::const_base_ref const _window
)
:
	window_{
		_window
	},
	signals_{}
{
}

template<
	typename Event
>
sge::x11input::event::demuxer<
	Event
>::~demuxer()
= default;

template<
	typename Event
>
awl::backends::x11::window::base const &
sge::x11input::event::demuxer<
	Event
>::window() const
{
	return
		window_.get();
}

template<
	typename Event
>
fcppt::signal::auto_connection
sge::x11input::event::demuxer<
	Event
>::on_event(
	sge::x11input::device::id const _id,
	function _function
)
{
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

	return
		fcppt::container::get_or_insert(
			signals_,
			_id,
			[](
				sge::x11input::device::id
			)
			{
				return
					signal_type{
						typename
						signal_type::combiner_function{
							&sge::window::event_combiner
						}
					};
			}
		).connect(
			std::move(
				_function
			),
			fcppt::signal::unregister::function{
				[
					this,
					_id
				]()
				{
					fcppt::optional::maybe_void(
						fcppt::container::find_opt_iterator(
							signals_,
							_id
						),
						[
							this
						](
							typename
							signal_map::iterator const _it
						)
						{
							if(
								_it->second.empty()
							)
							{
								signals_.erase(
									_it
								);
							}
						}
					);
				}
			}
		);

	FCPPT_PP_POP_WARNING
}

template<
	typename Event
>
awl::event::container
sge::x11input::event::demuxer<
	Event
>::call(
	Event const &_event
)
{
	return
		fcppt::optional::maybe(
			fcppt::container::find_opt_mapped(
				signals_,
				sge::x11input::device::id{
					_event.deviceid
				}
			),
			[]{
				return
					awl::event::container{};
			},
			[
				&_event
			](
				fcppt::reference<
					signal_type
				> const _device_signal
			)
			{
				return
					_device_signal.get()(
						typename
						signal_type::initial_value{
							awl::event::container{}
						},
						_event
					);
			}
		);
}

#endif
