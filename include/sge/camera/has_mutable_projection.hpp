#ifndef SGE_CAMERA_HAS_MUTABLE_PROJECTION_HPP_INCLUDED
#define SGE_CAMERA_HAS_MUTABLE_PROJECTION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL has_mutable_projection
{
FCPPT_NONCOPYABLE(
	has_mutable_projection);
protected:
	SGE_CAMERA_SYMBOL
	explicit
	has_mutable_projection();
public:
	virtual void
	projection_matrix(
		sge::camera::projection_matrix const &) = 0;

	SGE_CAMERA_SYMBOL
	virtual ~has_mutable_projection() = 0;
};
}
}

#endif

