//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_ALGORITHM_CLONE_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_CLONE_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/clone.hpp>
#include <sge/image/store/basic.hpp>
#include <sge/image/store/object.hpp>
#include <sge/image/view/const_object.hpp>
#include <mizuiro/image/algorithm/clone.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename Tag
>
sge::image::store::object<
	Tag
>
sge::image::algorithm::clone(
	sge::image::view::const_object<
		Tag
	> const &_view
)
{
	return
		fcppt::variant::apply(
			[](
				auto const &_inner_view
			)
			{
				return
					sge::image::store::object<
						Tag
					>{
						sge::image::store::basic<
							typename
							std::decay<
								decltype(
									_inner_view
								)
							>::type::format
						>(
							mizuiro::image::algorithm::clone(
								_inner_view
							)
						)
					};
			},
			_view.get()
		);
}

#endif
