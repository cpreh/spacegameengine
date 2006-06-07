#include "../image.hpp"
#include <IL/ilu.h>

sge::devil::image::image(const std::string& file)
{
	ILuint temp;
	ilGenImages(1,&temp);
	id = new im_guard(temp);
	bind_me();
	if(ilLoadImage(const_cast<char*>(file.c_str())) == IL_FALSE)
		throw std::runtime_error(std::string("ilLoadImage() failed!"));
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);
}

void sge::devil::image::bind_me() const
{
	ilBindImage(*id);
}

sge::image::size_type sge::devil::image::width() const { return w; }
sge::image::size_type sge::devil::image::height() const { return h; }

sge::image::const_pointer sge::devil::image::data() const
{
	bind_me();
	return reinterpret_cast<color*>(ilGetData());
}

void sge::devil::image::resize(const size_type _w, const size_type _h)
{
	if(_w == w && _h == h)
		return;
	bind_me();
	if(iluScale(_w,_h,32) == IL_FALSE)
		throw std::runtime_error("iluScale() failed!");
	w = _w;
	h = _h;
}
