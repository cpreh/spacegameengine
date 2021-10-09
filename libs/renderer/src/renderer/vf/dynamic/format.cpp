//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::renderer::vf::dynamic::format::format(sge::renderer::vf::dynamic::part_list &&_parts)
    : parts_(std::move(_parts))
{
}

sge::renderer::vf::dynamic::part_list const &sge::renderer::vf::dynamic::format::parts() const
{
  return this->parts_;
}
