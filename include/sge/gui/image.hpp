#ifndef SGE_GUI_IMAGE_HPP_INCLUDED
#define SGE_GUI_IMAGE_HPP_INCLUDED

#include <sge/gui/dim.hpp>
#include <sge/gui/image_view.hpp>
#include <sge/renderer/image.hpp>
#include <sge/shared_ptr.hpp>

namespace sge
{
namespace gui
{
// this wraps the gil stuff in renderer::rgba8_image (such as the dimension
// type being coord_t)
class image
{
public:
	typedef renderer::rgba8_image impl_type;

	image();
	explicit image(dim const &);
	impl_type &impl();
	impl_type const &impl() const;
	dim const size() const;
	image_view const view();
	const_image_view const const_view() const;
	void resize(dim const &);
private:
	impl_type impl_;
};
}
}

#endif
