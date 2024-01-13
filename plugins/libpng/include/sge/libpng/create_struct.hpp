//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_CREATE_STRUCT_HPP_INCLUDED
#define SGE_LIBPNG_CREATE_STRUCT_HPP_INCLUDED

#include <sge/libpng/error_context.hpp>
#include <sge/libpng/error_context_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <png.h>
#include <fcppt/config/external_end.hpp>

namespace sge::libpng
{

template <typename Function>
png_structp create_struct(
    Function const _function, sge::libpng::error_context_ref const _error_context)
{
  return _function(
      PNG_LIBPNG_VER_STRING,
      &_error_context.get(),
      &sge::libpng::error_context::handle_error,
      &sge::libpng::error_context::handle_warning);
}

}

#endif
