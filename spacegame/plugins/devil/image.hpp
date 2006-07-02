#ifndef SGE_DEVIL_IMAGE_HPP_INCLUDED
#define SGE_DEVIL_IMAGE_HPP_INCLUDED

#include "../../core/image/image_loader.hpp"
#include "../../core/main/shared_ptr.hpp"
#include "../../core/main/auto_ptr.hpp"
#include <IL/il.h>

namespace sge
{
namespace devil
{

class image : public sge::image {
public:
	image(const std::string& file);
	const_pointer data() const;
	size_type width() const;
	size_type height() const;
	void resize(size_type w, size_type h);
private:
	void bind_me() const;
	struct im_guard {
		im_guard(ILuint i) : i(i) {}
		~im_guard() { ilDeleteImages(1,&i); }
		operator ILuint() const { return i; }
	private:
		ILuint i;
	};
	typedef auto_ptr<im_guard> im_guard_ptr;
	im_guard_ptr id;
	size_type w, h;
};
typedef shared_ptr<image> image_ptr;

}
}

#endif

