//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/optional_base_ref.hpp>
#include <sge/opengl/info/const_context_ref.hpp>
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::opengl::context::object::object(sge::opengl::info::const_context_ref const _info)
    : info_(_info), elements_()
{
}

sge::opengl::context::object::~object() = default;

sge::opengl::context::optional_base_ref
sge::opengl::context::object::get(sge::opengl::context::id const _id)
{
  return fcppt::optional::deref(elements_[_id.get()]);
}

sge::opengl::context::base &sge::opengl::context::object::insert(
    sge::opengl::context::id const _id, sge::opengl::context::base_unique_ptr &&_ptr)
{
  optional_base_unique_ptr &dest(elements_[_id.get()]);

  sge::opengl::context::base &result(*_ptr);

  dest = optional_base_unique_ptr(std::move(_ptr));

  return result;
}

sge::opengl::info::context const &sge::opengl::context::object::info() const { return info_.get(); }
