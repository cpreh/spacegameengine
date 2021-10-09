//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::renderer::vertex::declaration_parameters::declaration_parameters(
    sge::renderer::vf::dynamic::format _format)
    : format_(std::move(_format))
{
}

sge::renderer::vf::dynamic::format const &
sge::renderer::vertex::declaration_parameters::format() const
{
  return format_;
}
