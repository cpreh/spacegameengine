//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_BASE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BASE_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
public:
	virtual
	cl_mem
	impl() = 0;

	virtual
	~base();
protected:
	base();
};

}
}
}

#endif
