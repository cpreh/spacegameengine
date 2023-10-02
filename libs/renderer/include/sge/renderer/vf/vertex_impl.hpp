//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_VERTEX_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_VERTEX_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/vertex_decl.hpp> // IWYU pragma: export
#include <fcppt/record/get.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Part>
template <typename... Args, typename>
sge::renderer::vf::vertex<Part>::vertex(Args &&..._args) : elements_{std::forward<Args>(_args)...}
{
}

template <typename Part>
template <typename Label>
fcppt::record::
    label_value_type<typename sge::renderer::vf::vertex<Part>::record_type, Label> const &
    sge::renderer::vf::vertex<Part>::get() const
{
  return fcppt::record::get<Label>(this->elements_);
}

template <typename Part>
template <typename Label>
void sge::renderer::vf::vertex<Part>::set(
    fcppt::record::label_value_type<record_type, Label> const &_value)
{
  fcppt::record::set<Label>(this->elements_, _value);
}

#endif
