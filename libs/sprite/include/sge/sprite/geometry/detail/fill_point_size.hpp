//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_POINT_SIZE_HPP_INCLUDED

#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/to_packed_type.hpp>
#include <sge/renderer/vf/labels/extra.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_point_size.hpp>
#include <sge/sprite/detail/vf/point_size.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	sge::sprite::detail::config::has_point_size<
		Choices
	>::value,
	void
>
fill_point_size(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	using
	point_size
	=
	sge::sprite::detail::vf::point_size<
		Choices
	>;

	sge::renderer::vf::set_proxy(
		*_iterator,
		sge::renderer::vf::labels::extra<
			point_size::index::value
		>{},
		sge::renderer::vf::to_packed_type<
			point_size
		>(
			static_cast<
				typename
				Choices::type_choices::float_type
			>(
				_sprite.point_size()
			)
		)
	);
}

template<
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	fcppt::not_(
		sge::sprite::detail::config::has_point_size<
			Choices
		>::value
	),
	void
>
fill_point_size(
	Iterator,
	sge::sprite::object<
		Choices
	> const &
)
{
}

}
}
}
}

#endif
