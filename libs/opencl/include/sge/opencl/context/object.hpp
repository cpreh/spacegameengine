//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/image/format_sequence.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opencl
{
namespace context
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_DETAIL_SYMBOL explicit
	object(
		context::parameters const &);

	SGE_OPENCL_DETAIL_SYMBOL cl_context
	impl() const;

	SGE_OPENCL_DETAIL_SYMBOL opencl::memory_object::image::format_sequence
	supported_planar_image_formats(
		cl_mem_flags) const;

	SGE_OPENCL_DETAIL_SYMBOL opencl::memory_object::image::format_sequence
	supported_volume_image_formats(
		cl_mem_flags) const;

	SGE_OPENCL_DETAIL_SYMBOL
	~object();
private:
	friend class opencl::platform::object;
	friend class opencl::command_queue::object;
	friend class opencl::program::object;

	cl_context context_;
	context::optional_error_callback const error_callback_;


	static void
	error_callback(
		char const *,
		void const *,
		size_t,
		void *);
};
}
}
}

#endif
