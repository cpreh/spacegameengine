#ifndef SGE_DEVIL_PIC_LOADER_HPP_INCLUDED
#define SGE_DEVIL_PIC_LOADER_HPP_INCLUDED

#include "../../core/main/shared_ptr.hpp"
#include "../../core/image/image_loader.hpp"

#include <IL/il.h>
#include <IL/ilu.h>
#include "./image.hpp"

namespace sge
{
namespace devil
{

class image_loader : public sge::image_loader {
public:
	image_loader();
	sge::image_ptr load_image(const std::string& path, unsigned w = 0, unsigned h = 0);
private:
	struct il_init_guard {
		il_init_guard() { ilInit(); iluInit(); }
		~il_init_guard() { ilShutDown(); }
	};
	il_init_guard g;
};

}
}

#endif

