//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_INFO_HPP_INCLUDED
#define SGE_LIBPNG_INFO_HPP_INCLUDED

#include <sge/libpng/info_fwd.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::libpng
{

class info
{
  FCPPT_NONMOVABLE(info);

public:
  explicit info(png_structp);

  ~info();

  [[nodiscard]] png_infop get() const;

private:
  png_structp const ptr_; // NOLINT(misc-misplaced-const)

  png_infop info_;
};

}

#endif
