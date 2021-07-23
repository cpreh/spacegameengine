//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_HAS_MUTABLE_PROJECTION_HPP_INCLUDED
#define SGE_CAMERA_HAS_MUTABLE_PROJECTION_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/optional_projection_matrix_fwd.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace camera
{

class SGE_CORE_DETAIL_CLASS_SYMBOL has_mutable_projection
:
	public virtual sge::camera::base
{
	FCPPT_NONMOVABLE(
		has_mutable_projection
	);
protected:
	SGE_CAMERA_DETAIL_SYMBOL
	has_mutable_projection();
public:
	virtual
	void
	update_projection_matrix(
		sge::camera::optional_projection_matrix const &
	) = 0;

	SGE_CAMERA_DETAIL_SYMBOL
	~has_mutable_projection()
	override;
};

}
}

#endif
