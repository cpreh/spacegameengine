/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>


sge::renderer::vf::dynamic::part::part(
	sge::renderer::vf::dynamic::element_list const &_elements,
	sge::renderer::vf::dynamic::offset_list const &_offsets
)
:
	elements_(
		[
			&_elements,
			&_offsets
		]{
			if(
				_elements.size()
				+
				1u
				!=
				_offsets.size()
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("dynamic::format: Invalid sizes of vectors!")
					};

			return
				fcppt::algorithm::map<
					sge::renderer::vf::dynamic::ordered_element_list
				>(
					fcppt::make_int_range_count(
						_elements.size()
					),
					[
						&_elements,
						&_offsets
					](
						sge::renderer::vf::dynamic::element_list::size_type const _index
					)
					{
						return
							sge::renderer::vf::dynamic::ordered_element(
								_elements[
									_index
								],
								_offsets[
									_index
								]
							);
					}
				);
		}()
	),
	stride_(
		sge::renderer::vf::dynamic::stride(
			_offsets.back().get()
		)
	)
{
}

sge::renderer::vf::dynamic::ordered_element_list const &
sge::renderer::vf::dynamic::part::elements() const
{
	return
		elements_;
}

sge::renderer::vf::dynamic::stride
sge::renderer::vf::dynamic::part::stride() const
{
	return
		stride_;
}
