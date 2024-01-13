//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_FILE_HPP_INCLUDED
#define SGE_LIBPNG_FILE_HPP_INCLUDED

#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/libpng/file_rep.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge::libpng
{

class file : public sge::image2d::file
{
  FCPPT_NONMOVABLE(file);

public:
  file(fcppt::log::object_reference, sge::libpng::file_rep &&);

  ~file() override;

private:
  [[nodiscard]] sge::image2d::view::const_object view() const override;

  [[nodiscard]] sge::image2d::dim size() const override;

  void save(std::filesystem::path const &) const override;

  void save_stream(std::ostream &) const override;

  fcppt::log::object_reference const log_;

  sge::libpng::file_rep const rep_;
};

}

#endif
