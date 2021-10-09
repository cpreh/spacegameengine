//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/md3/impl/axis_array.hpp>
#include <sge/model/md3/impl/max_qpath.hpp>
#include <sge/model/md3/impl/read_string.hpp>
#include <sge/model/md3/impl/read_vec3.hpp>
#include <sge/model/md3/impl/tag.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::model::md3::impl::tag::tag(std::istream &_stream)
    : name_(sge::model::md3::impl::read_string<sge::model::md3::impl::max_qpath::value>(_stream)),
      origin_(sge::model::md3::impl::read_vec3(_stream)),
      axis_(
          [&_stream]
          {
            sge::model::md3::impl::vec3 const axis1{sge::model::md3::impl::read_vec3(_stream)};

            sge::model::md3::impl::vec3 const axis2{sge::model::md3::impl::read_vec3(_stream)};

            sge::model::md3::impl::vec3 const axis3{sge::model::md3::impl::read_vec3(_stream)};

            return sge::model::md3::impl::axis_array{axis1, axis2, axis3};
          }())
{
}
