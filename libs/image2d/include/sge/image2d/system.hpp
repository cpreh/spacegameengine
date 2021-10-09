//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE2D_SYSTEM_HPP_INCLUDED
#define SGE_IMAGE2D_SYSTEM_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image2d/load_stream_result_fwd.hpp>
#include <sge/image2d/optional_file_unique_ptr_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::image2d
{

class SGE_CORE_DETAIL_CLASS_SYMBOL system
{
  FCPPT_NONMOVABLE(system);

protected:
  SGE_IMAGE2D_DETAIL_SYMBOL
  system();

public:
  [[nodiscard]] virtual sge::image2d::load_stream_result load_stream(
      sge::media::stream_unique_ptr &&,
      sge::media::optional_extension const &,
      sge::media::optional_name const &) = 0;

  [[nodiscard]] virtual sge::image2d::optional_file_unique_ptr
  create(sge::image2d::view::const_object const &, sge::media::extension const &) = 0;

  [[nodiscard]] virtual sge::media::extension_set extensions() const = 0;

  SGE_IMAGE2D_DETAIL_SYMBOL
  virtual ~system();
};

}

#endif
