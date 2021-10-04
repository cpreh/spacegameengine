//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_EXCEPTION_HPP_INCLUDED
#define SGE_IMAGE2D_EXCEPTION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/exception.hpp>
#include <sge/image2d/exception_fwd.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace sge::image2d
{

class SGE_CORE_DETAIL_CLASS_SYMBOL exception
:
	public sge::image::exception
{
public:
	SGE_IMAGE2D_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::assert_::information const &
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception(
		exception &&
	)
	noexcept;

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception(
		exception const &
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception &
	operator=(
		exception &&
	)
	noexcept;

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception &
	operator=(
		exception const &
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	~exception() noexcept
	override;
};

}

#endif
