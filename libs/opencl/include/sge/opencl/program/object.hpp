//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PROGRAM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>
#include <sge/opencl/program/build_parameters_fwd.hpp>
#include <sge/opencl/program/optional_build_parameters.hpp>
#include <sge/opencl/program/optional_notification_callback.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/raw_vector/object_fwd.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object.hpp>


namespace sge
{
namespace opencl
{
namespace program
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	object(
		fcppt::log::context &,
		sge::opencl::context::object &,
		sge::opencl::program::source_string_sequence const &,
		sge::opencl::program::optional_build_parameters const &);

	SGE_OPENCL_DETAIL_SYMBOL cl_program
	impl() const;

	SGE_OPENCL_DETAIL_SYMBOL void
	build(
		sge::opencl::program::build_parameters const &);

	SGE_OPENCL_DETAIL_SYMBOL ~object();
private:
	explicit
	object(
		fcppt::log::context &
	);

	friend class sge::opencl::kernel::object;

	typedef
	fcppt::container::raw_vector::object<
		cl_device_id
	>
	device_id_vector;

	fcppt::log::object log_;
	cl_program program_;
	sge::opencl::program::optional_notification_callback notification_callback_;

	device_id_vector
	program_devices() const;

	void
	check_program_return_values();

	static void
	notification_callback(
		cl_program,
		void *);
};
}
}
}

#endif
