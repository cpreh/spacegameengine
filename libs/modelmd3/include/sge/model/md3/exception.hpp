//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_EXCEPTION_HPP_INCLUDED
#define SGE_MODEL_MD3_EXCEPTION_HPP_INCLUDED

#include <sge/core/exception.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/model/md3/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge::model::md3
{

class SGE_CORE_DETAIL_CLASS_SYMBOL exception
:
	public sge::core::exception
{
public:
	SGE_MODEL_MD3_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);

	SGE_MODEL_MD3_DETAIL_SYMBOL
	exception(
		exception &&
	)
	noexcept;

	SGE_MODEL_MD3_DETAIL_SYMBOL
	exception(
		exception const &
	);

	SGE_MODEL_MD3_DETAIL_SYMBOL
	exception &
	operator=(
		exception &&
	)
	noexcept;

	SGE_MODEL_MD3_DETAIL_SYMBOL
	exception &
	operator=(
		exception const &
	);

	SGE_MODEL_MD3_DETAIL_SYMBOL
	~exception() noexcept
	override;
};

}

#endif
