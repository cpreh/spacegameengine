//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_MD3_LOADER_HPP_INCLUDED
#define SGE_MODEL_MD3_LOADER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/model/md3/load_flags_field_fwd.hpp>
#include <sge/model/md3/loader_fwd.hpp>
#include <sge/model/md3/object_unique_ptr.hpp>
#include <sge/model/md3/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge::model::md3
{

class SGE_CORE_DETAIL_CLASS_SYMBOL loader
{
  FCPPT_NONMOVABLE(loader);

protected:
  loader();

public:
  [[nodiscard]] virtual sge::model::md3::object_unique_ptr
  load(std::filesystem::path const &, sge::model::md3::load_flags_field) = 0;

  [[nodiscard]] virtual sge::model::md3::object_unique_ptr
  load_stream(std::istream &, sge::model::md3::load_flags_field) = 0;

  SGE_MODEL_MD3_DETAIL_SYMBOL
  virtual ~loader();
};

}

#endif
