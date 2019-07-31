//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_RESOURCE_MANAGER_HPP_INCLUDED
#define SGE_D3D9_RESOURCE_MANAGER_HPP_INCLUDED

#include <sge/d3d9/resource_fwd.hpp>
#include <sge/d3d9/resource_list.hpp>
#include <sge/d3d9/resource_manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{

class resource_manager
{
	FCPPT_NONCOPYABLE(
		resource_manager
	);
public:
	resource_manager();

	~resource_manager();

	void
	add(
		d3d9::resource &
	);

	void
	release();

	void
	reinit();
private:
	d3d9::resource_list resources_;
};

}
}

#endif
