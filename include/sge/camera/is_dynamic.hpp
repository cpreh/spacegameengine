#ifndef SGE_CAMERA_IS_DYNAMIC_HPP_INCLUDED
#define SGE_CAMERA_IS_DYNAMIC_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/update_duration.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL is_dynamic
{
FCPPT_NONCOPYABLE(
	is_dynamic);
protected:
	SGE_CAMERA_SYMBOL
	explicit
	is_dynamic();
public:
	virtual void
	update(
		camera::update_duration const &) = 0;

	SGE_CAMERA_SYMBOL
	virtual ~is_dynamic() = 0;
};
}
}

#endif

