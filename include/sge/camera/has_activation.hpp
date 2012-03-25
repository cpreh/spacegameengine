#ifndef SGE_CAMERA_HAS_ACTIVATION_HPP_INCLUDED
#define SGE_CAMERA_HAS_ACTIVATION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/symbol.hpp>


namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL has_activation
{
protected:
	SGE_CAMERA_SYMBOL
	explicit
	has_activation();
public:
	virtual bool
	is_active() const = 0;

	virtual void
	is_active(
		bool) = 0;

	void
	toggle_is_active();

	SGE_CAMERA_SYMBOL
	virtual ~has_activation() = 0;
};
}
}

#endif

