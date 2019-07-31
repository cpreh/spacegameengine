//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_SELECT_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_SELECT_HPP_INCLUDED

#include <sge/x11input/event/demuxer_decl.hpp>
#include <sge/x11input/event/select_unsafe.hpp>
#include <sge/x11input/event/static_type.hpp>
#include <sge/x11input/event/type.hpp>
#include <sge/x11input/event/type_container.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop_break_brigand.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/brigand/all_of.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

template<
	typename Events,
	typename EventType
>
void
select(
	sge::x11input::event::demuxer<
		EventType
	> const &_demuxer,
	sge::x11input::device::id const _id
)
{
	static_assert(
		fcppt::brigand::all_of<
			Events,
			brigand::bind<
				std::is_same,
				brigand::bind<
					sge::x11input::event::static_type,
					brigand::_1
				>,
				brigand::pin<
					EventType
				>
			>
		>::value,
		"Invalid device event"
	);

	sge::x11input::event::select_unsafe(
		_demuxer.window(),
		_id,
		fcppt::algorithm::map<
			sge::x11input::event::type_container
		>(
			Events{},
			[](
				auto const _tag
			)
			{
				FCPPT_USE(
					_tag
				);

				return
					sge::x11input::event::type{
						fcppt::tag_type<
							decltype(
								_tag
							)
						>::value
					};
			}
		)
	);
}

}
}
}

#endif
