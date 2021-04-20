//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_ALGORITHM_COPY_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COPY_IMPL_HPP_INCLUDED

#include <sge/image/invalid_copy.hpp>
#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/algorithm/copy.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/convert_may_overlap.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/format.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <sge/image/view/object.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <mizuiro/image/algorithm/copy.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename Tag
>
void
sge::image::algorithm::copy(
	sge::image::view::const_object<
		Tag
	> const &_src,
	sge::image::view::object<
		Tag
	> const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	fcppt::variant::apply(
		[
			&_src,
			&_dest,
			_overlap,
			_uninitialized
		](
			auto const &_src_inner
		)
		{
			return
				mizuiro::image::algorithm::copy(
					_src_inner,
					fcppt::optional::to_exception(
						fcppt::variant::to_optional<
							sge::image::view::mizuiro_type<
								typename
								std::decay_t<
									decltype(
										_src_inner
									)
								>::format,
								mizuiro::nonconst_tag
							>
						>(
							_dest.get()
						),
						[
							&_src,
							&_dest
						]{
							return
								sge::image::invalid_copy<
									sge::image::traits::image::color_tag<
										Tag
									>
								>{
									sge::image::view::format<
										Tag
									>(
										_src
									),
									sge::image::view::format<
										Tag
									>(
										_dest
									)
								};
						}
					),
					sge::image::impl::algorithm::convert_may_overlap(
						_overlap
					),
					sge::image::impl::algorithm::convert_uninitialized(
						_uninitialized
					)
				);
		},
		_src.get()
	);
}

#endif
