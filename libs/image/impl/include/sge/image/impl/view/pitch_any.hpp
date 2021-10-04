//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_PITCH_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_PITCH_ANY_HPP_INCLUDED

#include <sge/image/pitch.hpp>
#include <sge/image/impl/from_mizuiro_dim.hpp>
#include <fcppt/variant/apply.hpp>


namespace sge::image::impl::view
{

template<
	typename Tag,
	typename View
>
sge::image::pitch<
	Tag
>
pitch_any(
	View const &_view
)
{
	return
		fcppt::variant::apply(
			[](
				auto const &_src
			)
			{
				return
					sge::image::impl::from_mizuiro_dim(
						_src.pitch()
					);
			},
			_view.get()
		);
}

}

#endif
