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


#ifndef SGE_SRC_RENDERER_VF_DYNAMIC_DETAIL_CONVERTER_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_VF_DYNAMIC_DETAIL_CONVERTER_IMPL_HPP_INCLUDED

#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/converter_impl_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <sge/src/renderer/vf/dynamic/detail/element_converter_fwd.hpp>
#include <sge/src/renderer/vf/dynamic/detail/lock_interval.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
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
		dynamic::part const &,
		dynamic::color_format_vector const &
	);

	~converter_impl();

	void
	convert_lock(
		renderer::raw_pointer data,
		renderer::size_type pos,
		detail::lock_interval_set const &,
		detail::lock_interval const &
	);

	void
	convert_unlock(
		renderer::raw_pointer data,
		renderer::size_type pos,
		detail::lock_interval const &
	);
private:
	void
	do_convert(
		renderer::raw_pointer data,
		renderer::size_type pos,
		detail::lock_interval const &,
		bool unlock
	);

	typedef boost::ptr_vector<
		detail::element_converter
	> element_converter_vector;

	element_converter_vector element_converters_;
};

}
}
}
}
}

#endif
