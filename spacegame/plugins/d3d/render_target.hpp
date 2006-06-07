#ifndef SGE_D3D_RENDERTARGET_HPP_INCLUDED
#define SGE_D3D_RENDERTARGET_HPP_INCLUDED

#include "../../core/renderer/render_target.hpp"
#include "./resource.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
	namespace d3d
	{
		class renderer;

		class render_target : public sge::render_target, public resource {
			friend class renderer;
		public:
			render_target(renderer* r, d3d_device_ptr device, size_type width,
				          size_type height);
			size_type get_width() const;
			size_type get_height() const;
			size_type size() const;
			resource_flag_t get_flags() const;

			void restore();
			void on_loss();
		private:
			void init();

			d3d_texture_ptr  tex;
			d3d_device_ptr   device;
			d3d_surface_ptr  surface;
			size_type        width;
			size_type        height;
		};
	}
}

#endif
