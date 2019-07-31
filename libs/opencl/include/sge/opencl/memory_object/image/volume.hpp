//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_VOLUME_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_VOLUME_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/dim3.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/renderer/texture/volume_fwd.hpp>
#include <fcppt/math/dim/object_impl.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
class volume
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	volume);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	volume(
		context::object &,
		memory_object::flags_field const &,
		renderer::texture::volume &);

	SGE_OPENCL_DETAIL_SYMBOL cl_mem
	impl()
	override;

	SGE_OPENCL_DETAIL_SYMBOL cl_image_format const &
	image_format() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::dim3 const &
	size() const;

	SGE_OPENCL_DETAIL_SYMBOL ~volume()
	override;
private:
	cl_mem impl_;
	cl_image_format image_format_;
	sge::opencl::dim3 size_;
};
}
}
}
}

#endif
