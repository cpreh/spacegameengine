//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_ALGORITHM_PRINT_HPP_INCLUDED
#define SGE_IMAGE_ALGORITHM_PRINT_HPP_INCLUDED

#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>


namespace sge::image::algorithm
{

template<
	typename Tag
>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
void
print(
	fcppt::io::ostream &,
	sge::image::view::const_object<
		Tag
	> const &
);

}

#endif
