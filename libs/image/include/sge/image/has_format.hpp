//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_HAS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_HAS_FORMAT_HPP_INCLUDED

#include <sge/image/traits/pixel/static_formats.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
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
brigand::found<
	sge::image::traits::pixel::static_formats<
		Tag
	>,
	brigand::bind<
		std::is_same,
		brigand::pin<
			Format
		>,
		brigand::_1
	>
>;

}
}

#endif
