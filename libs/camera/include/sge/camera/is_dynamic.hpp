//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_IS_DYNAMIC_HPP_INCLUDED
#define SGE_CAMERA_IS_DYNAMIC_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace camera
{

class SGE_CORE_DETAIL_CLASS_SYMBOL is_dynamic
:
	public virtual sge::camera::base
{
	FCPPT_NONCOPYABLE(
		is_dynamic
	);
protected:
	SGE_CAMERA_DETAIL_SYMBOL
	is_dynamic();
public:
	virtual
	void
	update(
		sge::camera::update_duration
	) = 0;

	SGE_CAMERA_DETAIL_SYMBOL
	~is_dynamic()
	override;
};

}
}

#endif
