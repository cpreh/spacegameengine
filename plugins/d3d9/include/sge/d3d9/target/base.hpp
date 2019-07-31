//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TARGET_BASE_HPP_INCLUDED
#define SGE_D3D9_TARGET_BASE_HPP_INCLUDED

#include <sge/d3d9/target/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace target
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	void
	active(
		bool
	) = 0;

	virtual
	bool
	needs_present() const = 0;
};

}
}
}

#endif
