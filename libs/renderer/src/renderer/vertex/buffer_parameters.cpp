//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>

sge::renderer::vertex::buffer_parameters::buffer_parameters(
    sge::renderer::vertex::const_declaration_ref const _declaration,
    sge::renderer::vf::dynamic::part_index const _part,
    sge::renderer::vertex::count const _count,
    sge::renderer::resource_flags_field const &_flags)
    : declaration_(_declaration), part_(_part), count_(_count), flags_(_flags)
{
}

sge::renderer::vertex::declaration const &
sge::renderer::vertex::buffer_parameters::declaration() const
{
  return declaration_.get();
}

sge::renderer::vf::dynamic::part_index sge::renderer::vertex::buffer_parameters::part() const
{
  return part_;
}

sge::renderer::vertex::count sge::renderer::vertex::buffer_parameters::count() const
{
  return count_;
}

sge::renderer::resource_flags_field sge::renderer::vertex::buffer_parameters::flags() const
{
  return flags_;
}
