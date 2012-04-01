#ifndef SGE_CAMERA_ORTHO_FREELOOK_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/action/activate_pan.hpp>
#include <sge/camera/ortho_freelook/action/zoom_in.hpp>
#include <sge/camera/ortho_freelook/action/zoom_out.hpp>
#include <fcppt/optional_impl.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
namespace action
{
/**
\brief A mapping from camera "actions" to key codes
\ingroup sgecamera
*/
class mapping
{
public:
	SGE_CAMERA_SYMBOL
	explicit
	mapping(
		action::zoom_in const &,
		action::zoom_out const &,
		action::activate_pan const &);

	SGE_CAMERA_SYMBOL
	action::zoom_in const &
	zoom_in() const;

	SGE_CAMERA_SYMBOL
	action::zoom_out const &
	zoom_out() const;

	SGE_CAMERA_SYMBOL
	action::activate_pan const &
	activate_pan() const;
private:
	action::zoom_in zoom_in_;
	action::zoom_out zoom_out_;
	action::activate_pan activate_pan_;
};
}
}
}
}

#endif

