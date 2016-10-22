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


#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_DETAIL_CONVERTER_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_DETAIL_CONVERTER_IMPL_HPP_INCLUDED

#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter.hpp>
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/unlock.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/converter_impl_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
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

class converter_impl
{
	FCPPT_NONCOPYABLE(
		converter_impl
	);
public:
	converter_impl(
		sge::renderer::vf::dynamic::part const &,
		sge::renderer::vf::dynamic::color_format_vector const &
	);

	~converter_impl();

	void
	convert_lock(
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		sge::renderer::vf::dynamic::detail::lock_interval_set const &,
		sge::renderer::impl::vf::dynamic::lock_interval const &
	);

	void
	convert_unlock(
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		sge::renderer::impl::vf::dynamic::lock_interval const &
	);
private:
	void
	do_convert(
		sge::renderer::raw_pointer data,
		sge::renderer::vertex::first,
		sge::renderer::impl::vf::dynamic::lock_interval const &,
		sge::renderer::impl::vf::dynamic::unlock
	);

	typedef
	std::vector<
		sge::renderer::impl::vf::dynamic::element_converter
	>
	element_converter_vector;

	element_converter_vector const element_converters_;
};

}
}
}
}
}

#endif
