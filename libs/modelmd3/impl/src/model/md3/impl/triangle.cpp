//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/md3/impl/index_array.hpp>
#include <sge/model/md3/impl/read_s32.hpp>
#include <sge/model/md3/impl/triangle.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::model::md3::impl::triangle::triangle(std::istream &_stream)
    : // TODO(philipp): Direct initialization
      indices_(fcppt::no_init{})
{
  for (auto &index : indices_)
  {
    index = sge::model::md3::impl::read_s32(_stream);
  }
}

sge::model::md3::impl::index_array const &sge::model::md3::impl::triangle::indices() const
{
  return indices_;
}
