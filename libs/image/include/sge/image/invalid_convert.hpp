//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_INVALID_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_INVALID_CONVERT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/invalid_convert_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>


namespace sge
{
namespace image
{

template<
	typename Tag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL invalid_convert
:
	public sge::image::exception
{
public:
	typedef
	sge::image::traits::pixel::format<
		Tag
	>
	format;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert(
		format source,
		format dest
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert(
		invalid_convert &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert(
		invalid_convert const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert &
	operator=(
		invalid_convert &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert &
	operator=(
		invalid_convert const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~invalid_convert() noexcept
	override;
};

}
}

#endif
