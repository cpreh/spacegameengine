//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/md3/impl/max_qpath.hpp>
#include <sge/model/md3/impl/read_s32.hpp>
#include <sge/model/md3/impl/read_string.hpp>
#include <sge/model/md3/impl/shader.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::model::md3::impl::shader::shader(std::istream &_stream)
    : name_(sge::model::md3::impl::read_string<sge::model::md3::impl::max_qpath::value>(_stream)),
      shader_index_(sge::model::md3::impl::read_s32(_stream))
{
}
