//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/exception.hpp>
#include <sge/libpng/create_struct.hpp>
#include <sge/libpng/error_context_ref.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/write_ptr.hpp>
#include <fcppt/text.hpp>

sge::libpng::write_ptr::write_ptr(sge::libpng::error_context_ref const _error_context)
    : ptr_{sge::libpng::create_struct(&::png_create_write_struct, _error_context)}
{
  if (ptr_ == nullptr)
  {
    throw sge::image::exception{FCPPT_TEXT("couldn't allocate png write structure")};
  }
}

sge::libpng::write_ptr::~write_ptr() { ::png_destroy_write_struct(&ptr_, nullptr); }

png_structp sge::libpng::write_ptr::ptr() const { return ptr_; }
