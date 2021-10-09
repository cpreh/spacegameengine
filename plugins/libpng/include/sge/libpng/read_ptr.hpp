//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_READ_PTR_HPP_INCLUDED
#define SGE_LIBPNG_READ_PTR_HPP_INCLUDED

#include <sge/libpng/error_context_ref.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::libpng
{

class read_ptr
{
  FCPPT_NONMOVABLE(read_ptr);

public:
  explicit read_ptr(sge::libpng::error_context_ref);

  ~read_ptr();

  [[nodiscard]] png_structp ptr() const;

private:
  png_structp ptr_;
};

}

#endif
