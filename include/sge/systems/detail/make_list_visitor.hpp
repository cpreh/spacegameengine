/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_DETAIL_MAKE_LIST_VISITOR_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_LIST_VISITOR_HPP_INCLUDED

#include <sge/systems/cursor_demuxer_fwd.hpp>
#include <sge/systems/keyboard_collector_fwd.hpp>
#include <sge/systems/mouse_collector_fwd.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/has_input_option.hpp>
#include <sge/systems/detail/input.hpp>
#include <sge/systems/detail/list.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/detail/renderer_caps.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Choices,
	typename Inits
>
class make_list_visitor
{
	FCPPT_NONASSIGNABLE(
		make_list_visitor
	);
public:
	explicit
	make_list_visitor(
		sge::systems::detail::list &_result
	)
	:
		result_(
			_result
		)
	{
	}

	typedef void result_type;

	template<
		typename Type
	>
	result_type
	operator()(
		Type const &_type
	) const
	{
		// Check that the given parameter is actually part of the
		// static subsystems
		static_assert(
			boost::mpl::contains<
				boost::mpl::transform_view<
					Choices,
					sge::systems::detail::extract_parameter_type<
						boost::mpl::_
					>
				>,
				Type
			>::value,
			"Parameter given to sge::systems::list is not part of the system choices"
		);

		return
			this->add_impl(
				_type
			);
	}
private:
	template<
		typename Type
	>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::not_<
				std::is_same<
					Type,
					sge::systems::renderer
				>
			>,
			boost::mpl::not_<
				std::is_same<
					Type,
					sge::systems::input
				>
			>
		>,
		result_type
	>::type
	add_impl(
		Type const &_type
	) const
	{
		result_.insert(
			sge::systems::detail::any(
				_type
			)
		);
	}

	template<
		typename Type
	>
	typename boost::enable_if<
		std::is_same<
			sge::systems::renderer,
			Type
		>,
		result_type
	>::type
	add_impl(
		Type const &_renderer
	) const
	{
		result_.insert(
			sge::systems::detail::any(
				sge::systems::detail::renderer(
					_renderer,
					sge::systems::detail::renderer_caps<
						Choices
					>::value
				)
			)
		);
	}

	template<
		typename Type
	>
	typename boost::enable_if<
		std::is_same<
			sge::systems::input,
			Type
		>,
		result_type
	>::type
	add_impl(
		Type const &_input
	) const
	{
		result_.insert(
			sge::systems::detail::any(
				sge::systems::detail::input(
					_input,
					sge::systems::detail::input::cursor_demuxer(
						sge::systems::detail::has_input_option<
							Choices,
							sge::systems::cursor_demuxer
						>::value
					),
					sge::systems::detail::input::keyboard_collector(
						sge::systems::detail::has_input_option<
							Choices,
							sge::systems::keyboard_collector
						>::value
					),
					sge::systems::detail::input::mouse_collector(
						sge::systems::detail::has_input_option<
							Choices,
							sge::systems::mouse_collector
						>::value
					)
				)
			)
		);
	}
private:
	sge::systems::detail::list &result_;
};

}
}
}

#endif
