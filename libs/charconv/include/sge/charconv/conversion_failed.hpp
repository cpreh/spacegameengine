//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_CONVERSION_FAILED_HPP_INCLUDED
#define SGE_CHARCONV_CONVERSION_FAILED_HPP_INCLUDED

#include <sge/charconv/exception.hpp>
#include <sge/charconv/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>


namespace sge
{
namespace charconv
{

class SGE_CORE_DETAIL_CLASS_SYMBOL conversion_failed
:
	public sge::charconv::exception
{
public:
	SGE_CHARCONV_DETAIL_SYMBOL
	conversion_failed();

	SGE_CHARCONV_DETAIL_SYMBOL
	conversion_failed(
		conversion_failed &&
	);

	SGE_CHARCONV_DETAIL_SYMBOL
	conversion_failed(
		conversion_failed const &
	);

	SGE_CHARCONV_DETAIL_SYMBOL
	conversion_failed &
	operator=(
		conversion_failed &&
	);

	SGE_CHARCONV_DETAIL_SYMBOL
	conversion_failed &
	operator=(
		conversion_failed const &
	);

	SGE_CHARCONV_DETAIL_SYMBOL
	~conversion_failed() noexcept
	override;
};

}
}

#endif
