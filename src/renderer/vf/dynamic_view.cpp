/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/vf/dynamic_view.hpp>

template<typename Pointer>
sge::renderer::vf::basic_dynamic_view<Pointer>::basic_dynamic_view(
	pointer const data_,
	size_type const size_,
	dynamic_format const &format_)
:
	data_(data_),
	size_(size_),
	format_(format_)
{}

template<typename Pointer>
typename sge::renderer::vf::basic_dynamic_view<Pointer>::pointer
sge::renderer::vf::basic_dynamic_view<Pointer>::data() const
{
	return data_;
}

template<typename Pointer>
typename sge::renderer::vf::basic_dynamic_view<Pointer>::size_type
sge::renderer::vf::basic_dynamic_view<Pointer>::size() const
{
	return size_;
}

template<typename Pointer>
sge::renderer::vf::dynamic_format const &
sge::renderer::vf::basic_dynamic_view<Pointer>::format() const
{
	return format_;
}


#define SGE_VF_INSTANTIATE_DYNAMIC_VIEW(x)\
template class sge::renderer::vf::basic_dynamic_view<sge::renderer::vf::x>;

SGE_VF_INSTANTIATE_DYNAMIC_VIEW(raw_pointer)
SGE_VF_INSTANTIATE_DYNAMIC_VIEW(const_raw_pointer)

#undef SGE_VF_INSTANTIATE_DYNAMIC_VIEW
