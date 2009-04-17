#ifndef SGE_GUI_IMAGE_FWD_HPP_INCLUDED
#define SGE_GUI_IMAGE_FWD_HPP_INCLUDED

#include <sge/shared_ptr.hpp>

namespace sge
{
namespace gui
{
class image;
typedef shared_ptr<image> image_ptr;
typedef shared_ptr<image const> const_image_ptr;
}
}

#endif
