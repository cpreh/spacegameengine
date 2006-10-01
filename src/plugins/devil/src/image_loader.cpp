#include "../image_loader.hpp"
#include "../image.hpp"

sge::devil::image_loader::image_loader()
{
	ilEnable(IL_FORMAT_SET);
	ilSetInteger(IL_FORMAT_MODE,IL_RGBA);
}

sge::image_ptr sge::devil::image_loader::load_image(const std::string& path, const unsigned w, const unsigned h)
{
	image_ptr im(new image(path));
	
	if(w && h)
		im->resize(w,h);

	return im;
}

