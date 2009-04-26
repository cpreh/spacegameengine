/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/renderer/vf/dynamic_format.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::renderer::vf::dynamic_format::dynamic_format(
	dynamic_element_list const &elem,
	dynamic_offset_list const &offs)
{
	if(elem.size() + 1 != offs.size())
		throw exception(
			SGE_TEXT("dynamic_format: Invalid sizes of vectors!"));
	if(elem.empty() || offs.empty())
		throw exception(
			SGE_TEXT("dynamic_format: Format cannot be empty!"));
	for(dynamic_element_list::size_type i(0); i < elem.size(); ++i)
		elements_.push_back(
			dynamic_ordered_element(
				elem[i],
				offs[i]));
	stride_ = offs.back();
}

sge::renderer::vf::dynamic_ordered_element_list const &
sge::renderer::vf::dynamic_format::elements() const
{
	return elements_;
}

sge::renderer::vf::vertex_size
sge::renderer::vf::dynamic_format::stride() const
{
	return stride_;
}
