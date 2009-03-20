#ifndef SGE_GUI_IMAGE_HPP_INCLUDED
#define SGE_GUI_IMAGE_HPP_INCLUDED

#include <sge/renderer/image.hpp>
#include <sge/shared_ptr.hpp>

namespace sge
{
namespace gui
{
typedef renderer::rgba8_image image;
typedef shared_ptr<image> image_ptr;
typedef shared_ptr<image const> const_image_ptr;
}
}

#endif
