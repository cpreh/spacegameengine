#include "../image_loader.hpp"
#include "../image.hpp"

sge::devil::image_loader::image_loader()
{
	ilSetInteger(IL_FORMAT_MODE,IL_RGBA);
	ilEnable(IL_FORMAT_SET);
}

sge::image_ptr sge::devil::image_loader::load_image(const std::string& path, unsigned w, unsigned h)
{
	image_ptr im(new image(path));
	
	if(w && h)
		im->resize(w,h);

	return im;
}

