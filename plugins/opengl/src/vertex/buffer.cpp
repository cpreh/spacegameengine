//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/size_type.hpp>
#include <sge/opengl/buffer/stride.hpp>
#include <sge/opengl/buffer/vbo_context.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vertex/buffer.hpp>
#include <sge/opengl/vf/color_formats.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/renderer/dim1.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/dynamic/const_part_ref.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>

sge::opengl::vertex::buffer::buffer(
    sge::opengl::context::object_ref const _context,
    sge::renderer::vf::dynamic::part_index const _part_index,
    sge::renderer::vf::dynamic::part const &_format_part,
    sge::renderer::vertex::count const _size,
    sge::renderer::resource_flags_field const &_flags)
    : sge::renderer::vertex::buffer(),
      sge::opengl::buffer::wrapper(),
      part_index_(_part_index),
      format_part_(_format_part),
      converter_(fcppt::make_cref(format_part_), sge::opengl::vf::color_formats()),
      buffer_(
          fcppt::make_ref(
              sge::opengl::context::use<sge::opengl::buffer::vbo_context>(_context, _context)
                  .vertex_buffer()),
          sge::opengl::buffer::size_type{_size.get()},
          sge::opengl::buffer::stride{_format_part.stride().get()},
          _flags,
          nullptr)
{
}

sge::opengl::vertex::buffer::~buffer() = default;

void sge::opengl::vertex::buffer::use(sge::opengl::vf::part const &_format_part) const
{
  buffer_.bind();

  _format_part.use_me(buffer_.buffer_offset(0));
}

void sge::opengl::vertex::buffer::unuse( // NOLINT(readability-convert-member-functions-to-static)
    sge::opengl::vf::part const &_format_part) const
{
  _format_part.unuse_me();
}

sge::renderer::vf::dynamic::view sge::opengl::vertex::buffer::lock(
    sge::renderer::lock_segment const &_segment, sge::renderer::lock_mode const _flags)
{
  return this->do_lock<sge::renderer::vf::dynamic::view>(
      sge::renderer::lock_flags::from_mode(_flags), _segment);
}

sge::renderer::vf::dynamic::const_view
sge::opengl::vertex::buffer::lock_c(sge::renderer::lock_segment const &_segment) const
{
  return this->do_lock<sge::renderer::vf::dynamic::const_view>(
      sge::renderer::lock_flags::method::read, _segment);
}

template <typename View>
View sge::opengl::vertex::buffer::do_lock(
    sge::renderer::lock_flags::method const _method,
    sge::renderer::lock_segment const &_segment) const
{
  buffer_.lock(_method, _segment.pos().x(), _segment.size().w());

  converter_.lock(sge::renderer::vf::dynamic::locked_part(buffer_.data(), _segment, _method));

  return View(
      buffer_.data(),
      sge::renderer::vertex::count(buffer_.lock_size()),
      this->format(),
      part_index_);
}

void sge::opengl::vertex::buffer::unlock() const
{
  converter_.unlock();

  buffer_.unlock();
}

sge::renderer::dim1 sge::opengl::vertex::buffer::size() const
{
  return sge::renderer::dim1{buffer_.size()};
}

sge::renderer::resource_flags_field sge::opengl::vertex::buffer::resource_flags() const
{
  return buffer_.flags();
}

sge::renderer::vf::dynamic::const_part_ref sge::opengl::vertex::buffer::format() const
{
  return fcppt::make_cref(format_part_);
}

sge::renderer::vf::dynamic::part_index sge::opengl::vertex::buffer::format_part_index() const
{
  return part_index_;
}

sge::opengl::buffer::object const &sge::opengl::vertex::buffer::get() const { return buffer_; }
