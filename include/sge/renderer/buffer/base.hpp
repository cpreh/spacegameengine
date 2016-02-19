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


#ifndef SGE_RENDERER_BUFFER_BASE_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/traits/color_tag.hpp>
#include <sge/image/traits/dim_fwd.hpp>
#include <sge/image/traits/format_fwd.hpp>
#include <sge/image/traits/format_is_ref.hpp>
#include <sge/renderer/buffer/base_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace buffer
{

template<
	typename ImageTag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	base();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~base() = 0;

	/**
	\brief The image tag

	The image tag is used by generic algorithms that abstract 2D/3D and
	formats.
	*/
	typedef
	ImageTag
	image_tag;

	/**
	\brief The dimension type

	Specifies a dimension in pixels
	*/
	typedef
	typename
	sge::image::traits::dim<
		ImageTag
	>::type
	dim;

	/**
	\brief The color tag associated with the image tag
	*/
	typedef
	typename
	sge::image::traits::color_tag<
		ImageTag
	>::type
	format_tag;

	/**
	\brief The color format used by this buffer
	*/
	typedef
	typename
	sge::image::traits::format<
		format_tag
	>::type
	format_type;

	/**
	\brief The size of the buffer

	\return The size of the buffer as a size of pixels
	*/
	virtual
	dim
	size() const = 0;

	typedef
	typename
	boost::mpl::if_<
		sge::image::traits::format_is_ref<
			ImageTag
		>,
		format_type const &,
		format_type
	>::type
	format_return_type;

	/**
	\brief The format used by this buffer
	*/
	virtual
	format_return_type
	format() const = 0;
};

}
}
}

#endif
