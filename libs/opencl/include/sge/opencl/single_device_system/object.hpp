//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_SINGLE_DEVICE_SYSTEM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_SINGLE_DEVICE_SYSTEM_OBJECT_HPP_INCLUDED

#include <sge/opencl/binary_error_data.hpp>
#include <sge/opencl/error_information_string.hpp>
#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/single_device_system/object_fwd.hpp> // IWYU pragma: keep
#include <sge/opencl/single_device_system/parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <mutex>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::single_device_system
{
class object
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_OPENCL_DETAIL_SYMBOL
  object(fcppt::log::context_reference, sge::opencl::single_device_system::parameters const &);

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::system &system();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::system const &system() const;

  SGE_OPENCL_DETAIL_SYMBOL
  void update();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::object &platform();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::object const &platform() const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::device::object &device();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::device::object const &device() const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::context::object &context();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::context::object const &context() const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::command_queue::object &command_queue();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::command_queue::object const &
  command_queue() const;

  SGE_OPENCL_DETAIL_SYMBOL
  ~object();

private:
  fcppt::log::object log_;
  fcppt::unique_ptr<sge::opencl::system> const system_;
  sge::opencl::platform::object *platform_;
  sge::opencl::device::object *device_;
  fcppt::unique_ptr<sge::opencl::context::object> const context_;
  fcppt::unique_ptr<sge::opencl::command_queue::object> const queue_;
  std::mutex error_mutex_;
  bool error_occured_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
  sge::opencl::error_information_string error_information_;
  sge::opencl::binary_error_data error_data_;
  sge::opencl::context::optional_error_callback const error_callback_;

  void error_callback(
      sge::opencl::error_information_string const &, sge::opencl::binary_error_data const &);
};
}

#endif
