#ifndef SGE_IMAGE_LOADER_HPP_INCLUDED
#define SGE_IMAGE_LOADER_HPP_INCLUDED

#include <vector>
#include <string>
#include <boost/utility.hpp>
#include "../renderer/renderer_types.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/texture.hpp"
#include "../main/shared_ptr.hpp"
#include "./image.hpp"

namespace sge
{
	class image_loader {
	public:
		virtual image_ptr load_image(const std::string& path, unsigned w = 0, unsigned h = 0) = 0;
		virtual ~image_loader(){}
	};
	typedef shared_ptr<image_loader> image_loader_ptr;

	inline texture_ptr create_texture(renderer_ptr r, image_ptr p, unsigned mip_levels = 1, resource_flag_t flags = RF_Default)
	{
		return r->create_texture(p->data(),p->width(),p->height(),mip_levels,flags);
	}
	inline texture_ptr create_texture(const std::string& path, renderer_ptr r, image_loader_ptr p, unsigned w = 0, unsigned h = 0, unsigned mip_levels = 1, resource_flag_t flags = RF_Default)
	{
		return create_texture(r,p->load_image(path,w,h),mip_levels,flags);
	}	
}

#endif
