#ifndef SGE_CXIMAGE_PIC_LOADER_HPP_INCLUDED
#define SGE_CXIMAGE_PIC_LOADER_HPP_INCLUDED

#include <string>
#include "../../core/picloader/pic_loader.hpp"

namespace sge
{
	namespace cximage
	{
		class pic_loader : public sge::pic_loader {
		public:
			void create_pic(const std::string& file, pixel_array& array,
			                unsigned w = 0, unsigned h = 0);
			texture_ptr create_texture(renderer_ptr device, const std::string& path,
			                           unsigned mip_levels, unsigned flags, 
			                           unsigned w = 0, unsigned h = 0);
		};
	}
}

#endif
