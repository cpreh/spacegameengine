//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_CREATE_STRUCT_HPP_INCLUDED
#define SGE_LIBPNG_CREATE_STRUCT_HPP_INCLUDED

#include <sge/libpng/error_context.hpp>
#include <sge/libpng/png.hpp>


namespace sge
{
namespace libpng
{

template<
	typename Function
>
png_structp
create_struct(
	Function const _function,
	sge::libpng::error_context &_error_context
)
{
	return
		_function(
			PNG_LIBPNG_VER_STRING,
			&_error_context,
			&sge::libpng::error_context::handle_error,
			&sge::libpng::error_context::handle_warning
		);
}

}
}

#endif
