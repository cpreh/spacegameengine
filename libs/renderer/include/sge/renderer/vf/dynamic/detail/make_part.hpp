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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_PART_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/detail/make_element.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/size.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

template<
	typename Part
>
sge::renderer::vf::dynamic::part
make_part()
{
	typedef
	typename
	Part::elements
	elements;

	typedef
	typename
	Part::offsets
	offsets;

	sge::renderer::vf::dynamic::element_list elems;

	elems.reserve(
		boost::mpl::size<
			elements
		>::value
	);

	fcppt::mpl::for_each<
		elements
	>(
		[
			&elems
		](
			auto const &_tag
		)
		{
			FCPPT_USE(
				_tag
			);

			elems.push_back(
				sge::renderer::vf::dynamic::detail::make_element(
					fcppt::tag_type<
						decltype(
							_tag
						)
					>{}
				)
			);
		}
	);

	sge::renderer::vf::dynamic::offset_list offs;

	offs.reserve(
		boost::mpl::size<
			offsets
		>::value
	);

	fcppt::mpl::for_each<
		offsets
	>(
		[
			&offs
		](
			auto const &_tag
		)
		{
			FCPPT_USE(
				_tag
			);

			offs.push_back(
				sge::renderer::vf::dynamic::offset{
					fcppt::tag_type<
						decltype(
							_tag
						)
					>::value
				}
			);

		}
	);

	return
		sge::renderer::vf::dynamic::part(
			std::move(
				elems
			),
			std::move(
				offs
			)
		);
}

}
}
}
}
}

#endif
