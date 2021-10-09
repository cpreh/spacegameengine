//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/md3/texcoord.hpp>
#include <sge/model/md3/impl/read_scalar.hpp>
#include <sge/model/md3/impl/texpos.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::model::md3::impl::texpos::texpos(std::istream &_stream)
    : x_(sge::model::md3::impl::read_scalar(_stream)),
      y_(sge::model::md3::impl::read_scalar(_stream))
{
}

sge::model::md3::texcoord sge::model::md3::impl::texpos::texcoord() const
{
  return sge::model::md3::texcoord(x_, y_);
}
