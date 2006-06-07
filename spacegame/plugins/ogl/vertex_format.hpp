#ifndef SGE_OGL_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_OGL_VERTEX_FORMAT_HPP_INCLUDED

#include "../../core/main/shared_ptr.hpp"
#include "../../core/renderer/renderer_types.hpp"
#include "../../core/renderer/vertex_format.hpp"
#include "../../core/renderer/vertex_buffer.hpp"
#include <vector>

namespace sge
{
	namespace ogl
	{
		inline void* vbo_offset(const size_t sz)
		{
			return reinterpret_cast<void*>(sz);
		}

		struct actor_info {
			actor_info(vertex_size offset, vertex_size stride, vertex_size index)
				: offset(vbo_offset(offset)), stride(stride), index(index) {}
			void*       offset;
			vertex_size stride;
			vertex_size index;
		};

		class actor_base {
		public:
			actor_base(const actor_info& ai)
				: ai(ai) {}
			virtual ~actor_base(){}
			virtual void operator()() const = 0;
		protected:
			actor_info ai;
		};
		
		class vertex_format {
		public:
			vertex_format(const sge::vertex_format& f);
			const offset_info& get_oi() const { return oi; }
			void use_me();
		private:
			offset_info oi;
			typedef shared_ptr<actor_base> actor_base_ptr;
			typedef std::vector<actor_base_ptr> actor_array;
			actor_array actors;
		};
	}
}

#endif

