//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_BUFFER_BASE_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/dim_fwd.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/renderer/buffer/base_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>


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
	FCPPT_NONMOVABLE(
		base
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	base();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~base();

	using
	image_tag
	=
	ImageTag;

	using
	dim
	=
	sge::image::dim<
		ImageTag
	>;

	using
	format_tag
	=
	sge::image::traits::image::color_tag<
		ImageTag
	>;

	using
	format_type
	=
	sge::image::traits::pixel::format<
		format_tag
	>;

	[[nodiscard]]
	virtual
	dim
	size() const = 0;

	[[nodiscard]]
	virtual
	format_type
	format() const = 0;
};

}
}
}

#endif
