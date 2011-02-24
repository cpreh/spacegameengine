/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::renderer::vf::dynamic::part::part(
	element_list const &_elements,
	offset_list const &_offsets
)
{
	if(
		_elements.size() + 1u != _offsets.size()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("dynamic::format: Invalid sizes of vectors!")
		);

	if(
		_elements.empty() || _offsets.empty()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("dynamic::format: Format cannot be empty!")
		);

	for(
		element_list::size_type i(0);
		i < _elements.size();
		++i
	)
		elements_.push_back(
			dynamic::ordered_element(
				_elements[i],
				_offsets[i]
			)
		);

	stride_ = _offsets.back();
}

sge::renderer::vf::dynamic::ordered_element_list const &
sge::renderer::vf::dynamic::part::elements() const
{
	return elements_;
}

sge::renderer::vf::vertex_size
sge::renderer::vf::dynamic::part::stride() const
{
	return stride_;
}
