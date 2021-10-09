//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_ERROR_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_ERROR_CONTEXT_HPP_INCLUDED

#include <sge/libpng/error_context_fwd.hpp>
#include <sge/libpng/png.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object.hpp>

namespace sge::libpng
{

class error_context
{
  FCPPT_NONMOVABLE(error_context);

public:
  error_context(fcppt::log::object_reference, sge::media::optional_name &&);

  ~error_context();

  static void handle_warning(png_structp, png_const_charp);

  static void handle_error(png_structp, png_const_charp);

private:
  fcppt::log::object_reference const log_;

  sge::media::optional_name const name_;

  void handle_warning_impl(png_const_charp);

  [[noreturn]] void handle_error_impl(png_const_charp);

  static error_context &get_instance(png_structp);
};

}

#endif
