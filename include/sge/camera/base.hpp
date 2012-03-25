#ifndef SGE_CAMERA_BASE_HPP_INCLUDED
#define SGE_CAMERA_BASE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(
	base);
protected:
	explicit
	base();
public:
	virtual coordinate_system::object const
	coordinate_system() const = 0;

	virtual camera::projection_matrix const
	projection_matrix() const = 0;

	SGE_CAMERA_SYMBOL
	virtual ~base() = 0;
};
}
}

#endif

