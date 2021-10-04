//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_ENABLE_IF_HAS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_ENABLE_IF_HAS_FORMAT_HPP_INCLUDED

#include <sge/image/has_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::image
{

template<
	typename Tag,
	typename Format,
	typename Result
>
using
enable_if_has_format
=
std::enable_if_t<
	sge::image::has_format<
		Tag,
		Format
	>::value,
	Result
>;

}

#endif
