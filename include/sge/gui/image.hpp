#ifndef SGE_GUI_IMAGE_HPP_INCLUDED
#define SGE_GUI_IMAGE_HPP_INCLUDED

#include <sge/gui/dim.hpp>
#include <sge/gui/image_fwd.hpp>
#include <sge/gui/image_view.hpp>
#include <sge/renderer/image.hpp>

namespace sge
{
namespace gui
{
// this wraps the gil stuff in renderer::rgba8_image (such as the dimension
// type being coord_t)
class image
{
public:
	image();
	explicit image(dim const &);
	dim const size() const;
	image_view const view();
	const_image_view const const_view() const;
	void resize(dim const &);
private:
	typedef renderer::rgba8_image impl_type;
	impl_type impl_;
};
}
}

#endif
