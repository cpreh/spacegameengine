//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/visitor.hpp>
#include <sge/image/color/impl/dynamic/format/object_decl.hpp>
#include <sge/image/color/impl/dynamic/format/object_traits.hpp>
#include <sge/image/color/impl/dynamic/view/from_static_visitor.hpp>
#include <sge/image/traits/image/dimension.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <mizuiro/const_tag.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <fcppt/variant/apply.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace algorithm
{

template<
	typename Tag
>
void
copy_and_convert(
	sge::image::view::const_object<
		Tag
	> const &_source,
	sge::image::view::object<
		Tag
	> const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	using
	dim
	=
	sge::image::traits::image::dimension<
		Tag
	>;

	fcppt::variant::apply(
		sge::image::color::impl::dynamic::algorithm::cac::visitor(
			_overlap,
			_uninitialized
		),
		fcppt::variant::apply(
			sge::image::color::impl::dynamic::view::from_static_visitor<
				dim::value,
				mizuiro::const_tag
			>(),
			_source.get()
		),
		fcppt::variant::apply(
			sge::image::color::impl::dynamic::view::from_static_visitor<
				dim::value,
				mizuiro::nonconst_tag
			>(),
			_dest.get()
		)
	);
}

}
}
}
}
}
}

#endif
