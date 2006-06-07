#ifndef SGE_D3D_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_D3D_VOLUME_TEXTURE_HPP_INCLUDED

#include "../../core/renderer/volume_texture.hpp"
#include "./resource.hpp"
#include "./texture_base.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
	namespace d3d
	{
		class renderer;

		class volume_texture : public d3d::texture_base, public sge::volume_texture, public resource {
			friend class renderer;
		private:
			volume_texture(renderer* r, d3d_device_ptr device, const_pointer src,
			               size_type width, size_type height, size_type depth, resource_flag_t flags);
		public:
			size_type get_width() const;
			size_type get_height() const;
			size_type get_depth() const;

			size_type size() const;
			void set_data(const_pointer src, const lock_box* b);

			void on_loss();
			void restore();
			resource_flag_t get_flags() const;
			
			void lock(const lock_box* b);
			void unlock();
		private:
			void init();
			
			d3d_device_ptr          device;
			d3d_volume_texture_ptr  tex;
			d3d_volume_texture_ptr  temp_tex;
			pointer                 lock_dest;
			resource_flag_t         flags;
			size_type               width;
			size_type               height;
			size_type               depth;
		};
	}
}

#endif
