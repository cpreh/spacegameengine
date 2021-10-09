//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/lock_flags.hpp>
#include <sge/d3d9/convert/resource_flags.hpp>
#include <sge/d3d9/convert/resource_flags_to_pool.hpp>
#include <sge/d3d9/devicefuncs/create_vertex_buffer.hpp>
#include <sge/d3d9/vertex/buffer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/dim1.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/const_part_ref.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/object_impl.hpp>

sge::d3d9::vertex::buffer::buffer(
    IDirect3DDevice9 &_device,
    sge::renderer::vf::dynamic::part const &_format_part,
    sge::renderer::vertex::buffer_parameters const &_parameters)
    : sge::renderer::vertex::buffer(),
      sge::d3d9::resource(sge::d3d9::convert::resource_flags_to_pool(_parameters.flags())),
      device_(_device),
      format_part_(_format_part),
      format_part_index_(_parameters.part()),
      size_(_parameters.count()),
      resource_flags_(_parameters.flags()),
      converter_(
          fcppt::make_cref(format_part_),
          sge::renderer::vf::dynamic::color_format_vector{sge::image::color::format::bgra8}),
      buffer_(),
      lock_dest_(nullptr)
{
  this->init();
}

sge::d3d9::vertex::buffer::~buffer() {}

sge::renderer::vf::dynamic::view sge::d3d9::vertex::buffer::lock(
    sge::renderer::lock_segment const &_segment, sge::renderer::lock_mode const _lock_mode)
{
  return this->do_lock<sge::renderer::vf::dynamic::view>(
      _segment, sge::renderer::lock_flags::from_mode(_lock_mode));
}

sge::renderer::vf::dynamic::const_view
sge::d3d9::vertex::buffer::lock_c(sge::renderer::lock_segment const &_segment) const
{
  return this->do_lock<sge::renderer::vf::dynamic::const_view>(
      _segment, sge::renderer::lock_flags::method::read);
}

void sge::d3d9::vertex::buffer::unlock() const
{
  // TODO: Move this
  if (lock_dest_ == nullptr)
    throw sge::renderer::exception(
        FCPPT_TEXT("d3d9::vertex::buffer::unlock() you have to lock first!"));

  converter_.unlock();

  if (this->get().Unlock() != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("Cannot unlock d3d vertex buffer!"));

  lock_dest_ = nullptr;
}

sge::renderer::dim1 sge::d3d9::vertex::buffer::size() const
{
  return sge::renderer::dim1{size_.get()};
}

sge::renderer::resource_flags_field sge::d3d9::vertex::buffer::resource_flags() const
{
  return resource_flags_;
}

sge::renderer::vf::dynamic::const_part_ref sge::d3d9::vertex::buffer::format() const
{
  return fcppt::make_cref(format_part_);
}

sge::renderer::vf::dynamic::part_index sge::d3d9::vertex::buffer::format_part_index() const
{
  return format_part_index_;
}

sge::renderer::vf::dynamic::stride sge::d3d9::vertex::buffer::stride() const
{
  return format_part_.stride();
}

IDirect3DVertexBuffer9 &sge::d3d9::vertex::buffer::get() const
{
  return *FCPPT_ASSERT_OPTIONAL_ERROR(buffer_);
}

void sge::d3d9::vertex::buffer::init()
{
  buffer_ = optional_d3d_vertex_buffer_unique_ptr(sge::d3d9::devicefuncs::create_vertex_buffer(
      device_,
      this->stride().get() * size_.get(),
      this->pool(),
      sge::d3d9::convert::resource_flags(this->resource_flags())));
}

void sge::d3d9::vertex::buffer::on_loss()
{
  converter_.reset();

  buffer_ = optional_d3d_vertex_buffer_unique_ptr();
}

void sge::d3d9::vertex::buffer::on_reset() { this->init(); }

template <typename View>
View sge::d3d9::vertex::buffer::do_lock(
    sge::renderer::lock_segment const &_segment,
    sge::renderer::lock_flags::method const _method) const
{
  if (lock_dest_)
    throw sge::renderer::exception(
        FCPPT_TEXT("d3d::vertex::buffer::lock() you have to unlock first!"));

  // TODO: Put this in another function
  void *data(nullptr);

  if (this->get().Lock(
          fcppt::cast::size<UINT>(_segment.pos().x() * this->stride().get()),
          fcppt::cast::size<UINT>(_segment.size().w() * this->stride().get()),
          &data,
          sge::d3d9::convert::lock_flags(_method, this->resource_flags()).get()) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("Cannot lock d3d vertex buffer!"));

  lock_dest_ = fcppt::cast::from_void_ptr<sge::renderer::raw_pointer>(data);

  converter_.lock(sge::renderer::vf::dynamic::locked_part(lock_dest_, _segment, _method));

  return View(
      lock_dest_,
      sge::renderer::vertex::count{_segment.size().w()},
      this->format(),
      this->format_part_index());
}
