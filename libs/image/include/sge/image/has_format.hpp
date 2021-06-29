//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_HAS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_HAS_FORMAT_HPP_INCLUDED

#include <sge/image/traits/pixel/static_formats.hpp>
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/any_of.hpp>
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
fcppt::mpl::list::any_of<
	sge::image::traits::pixel::static_formats<
		Tag
	>,
	fcppt::mpl::bind<
		fcppt::mpl::lambda<
			std::is_same
		>,
		fcppt::mpl::constant<
			Format
		>,
		fcppt::mpl::arg<1>
	>
>;

}
}

#endif
