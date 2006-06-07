#ifndef SGE_D3D_VERTEXBUFFER_HPP_INCLUDED
#define SGE_D3D_VERTEXBUFFER_HPP_INCLUDED

#include "../../core/renderer/vertex_buffer.hpp"
#include "./vertex_format.hpp"
#include "./resource.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
	namespace d3d
	{
		class renderer;

		class vertex_buffer : public sge::vertex_buffer, public resource {
			friend class renderer;
		public:
			vertex_buffer(renderer* r, d3d_device_ptr device,
				          const sge::vertex_format& format, size_type size,
						  resource_flag_t flags, const_pointer src);
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			size_type size() const;
			void resize(size_type newsize);
			size_type get_stride() const;
			iterator create_iterator(pointer data) const;
			const_iterator create_iterator(const_pointer data) const;
			void lock(lock_flag_t flags, size_type first, size_type count);
			void unlock();
			void restore();
			resource_flag_t get_flags() const;
			void on_loss();
			const sge::vertex_format& get_vertex_format() const;
			pointer raw_data();
			const_pointer raw_data() const;
		private:
			void init(const_pointer src = 0);

			d3d_device_ptr        device;
			d3d_vertex_buffer_ptr buffer;
			pointer               lock_dest;
            resource_flag_t       flags;
			size_type             sz;
			sge::vertex_format    format;
			vertex_format         d3d_format;
		};
	}
}

#endif
