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


#ifndef SGE_X11INPUT_EVENT_SELECT_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_SELECT_HPP_INCLUDED

#include <sge/x11input/event/demuxer_decl.hpp>
#include <sge/x11input/event/select_unsafe.hpp>
#include <sge/x11input/event/static_type.hpp>
#include <sge/x11input/event/type.hpp>
#include <sge/x11input/event/type_container.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
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
		boost::mpl::fold<
			Events,
			boost::mpl::true_,
			boost::mpl::and_<
				boost::mpl::_1,
				std::is_same<
					sge::x11input::event::static_type<
						boost::mpl::_2
					>,
					EventType
				>
			>
		>::type::value,
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
