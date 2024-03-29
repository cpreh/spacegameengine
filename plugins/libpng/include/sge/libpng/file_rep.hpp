//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_FILE_REP_HPP_INCLUDED
#define SGE_LIBPNG_FILE_REP_HPP_INCLUDED

#include <sge/image2d/dim.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/file_rep_fwd.hpp>
#include <sge/libpng/format.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge::libpng
{

class file_rep
{
  FCPPT_NONCOPYABLE(file_rep);

public:
  file_rep(sge::image2d::dim, sge::libpng::format, sge::libpng::byte_vector &&);

  file_rep(file_rep &&) noexcept;

  file_rep &operator=(file_rep &&) noexcept;

  ~file_rep();

  [[nodiscard]] sge::image2d::dim size() const;

  [[nodiscard]] sge::libpng::format format() const;

  [[nodiscard]] sge::libpng::byte_vector const &bytes() const;

private:
  sge::image2d::dim size_;

  sge::libpng::format format_;

  sge::libpng::byte_vector bytes_;
};

}

#endif
