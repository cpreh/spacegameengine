//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_HAS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_HAS_FORMAT_HPP_INCLUDED

#include <sge/image/traits/pixel/static_formats.hpp>
#include <fcppt/mpl/set/contains.hpp>
#include <fcppt/mpl/set/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{

template<
	typename Tag,
	typename Format
>
using
has_format
=
fcppt::mpl::set::contains<
	fcppt::mpl::set::from_list<
		sge::image::traits::pixel::static_formats<
			Tag
		>
	>,
	Format
>;

}
}

#endif
