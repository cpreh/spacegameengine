//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_BUFFER_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_OBJECT_HPP_INCLUDED

#include <sge/opengl/buffer/base_ref.hpp>
#include <sge/opengl/buffer/count.hpp>
#include <sge/opengl/buffer/first_pos.hpp>
#include <sge/opengl/buffer/holder.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/object_fwd.hpp>
#include <sge/opengl/buffer/optional_id_fwd.hpp>
#include <sge/opengl/buffer/stride.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::opengl::buffer
{

class object
{
  FCPPT_NONMOVABLE(object);

public:
  using size_type = sge::renderer::size_type;

  using value_type = sge::renderer::raw_value;

  using pointer = value_type *;

  using const_pointer = value_type const *;

  using lock_flag_type = sge::renderer::lock_flags::method;

  using optional_first_pos = fcppt::optional::object<sge::opengl::buffer::first_pos>;

  using optional_count = fcppt::optional::object<sge::opengl::buffer::count>;

  object(
      sge::opengl::buffer::base_ref,
      sge::opengl::buffer::count,
      sge::opengl::buffer::stride,
      sge::renderer::resource_flags_field const &,
      const_pointer src);

  ~object();

  void lock(lock_flag_type const &, optional_first_pos, optional_count);

  void unlock();

  void sub_data(const_pointer data, sge::opengl::buffer::first_pos, sge::opengl::buffer::count);

  [[nodiscard]] size_type size() const;

  [[nodiscard]] size_type stride() const;

  [[nodiscard]] sge::renderer::resource_flags_field const &flags() const;

  [[nodiscard]] pointer data();

  [[nodiscard]] const_pointer data() const;

  [[nodiscard]] size_type lock_size() const;

  void unbind();

  void bind() const;

  [[nodiscard]] pointer buffer_offset(sge::opengl::buffer::first_pos) const;

  [[nodiscard]] pointer raw_buffer() const;

  [[nodiscard]] sge::opengl::buffer::id id() const;

  [[nodiscard]] bool native() const;

private:
  void bind_id(sge::opengl::buffer::optional_id const &) const;

  void do_unlock();

  sge::opengl::buffer::base_ref const base_;

  size_type const size_;

  size_type const stride_;

  sge::renderer::resource_flags_field const flags_;

  pointer dest_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  sge::opengl::buffer::holder const holder_;

  size_type lock_offset_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  size_type lock_size_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
