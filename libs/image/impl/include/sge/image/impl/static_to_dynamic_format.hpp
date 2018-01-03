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


#ifndef SGE_IMAGE_IMPL_STATIC_TO_DYNAMIC_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STATIC_TO_DYNAMIC_FORMAT_HPP_INCLUDED

#include <sge/image/impl/traits/pixel/format_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/pair.hpp>
#include <brigand/sequences/map.hpp>
#include <brigand/types/args.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace impl
{

// TODO: Move this to fcppt
template<
	typename T
>
struct flip_pair_impl;

template<
	typename T1,
	typename T2
>
struct flip_pair_impl<
	brigand::pair<
		T1,
		T2
	>
>
{
	typedef
	brigand::pair<
		T2,
		T1
	>
	type;
};

template<
	typename Pair
>
using
flip_pair
=
typename
flip_pair_impl<
	Pair
>::type;

template<
	typename Map
>
using
flip_map
=
brigand::transform<
	Map,
	brigand::bind<
		flip_pair,
		brigand::_1
	>
>;

template<
	typename ColorTag,
	typename StaticFormat
>
using
static_to_dynamic_format
=
brigand::lookup<
	flip_map<
	//fcppt::mpl::flip_map<
		sge::image::impl::traits::pixel::format_map<
			ColorTag
		>
	>,
	StaticFormat
>;

}
}
}

#endif
