#include "../extensions.hpp"
#include "../vertex_format.hpp"
#include "../error.hpp"
#include <stdexcept>

namespace {
	using sge::ogl::is_error;
	typedef sge::ogl::actor_base actor_base;
	typedef sge::ogl::actor_info actor_info;
	
	class pos_actor : public actor_base {
	public:
		pos_actor(const actor_info& ai)
			: actor_base(ai) {}
		void operator()() const
		{
			glVertexPointer(3,GL_FLOAT,ai.stride,ai.offset);
	                glEnableClientState(GL_VERTEX_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling positions on ogl stream failed!");
		}
	};

	class normal_actor : public actor_base {
	public:
		normal_actor(const actor_info& ai)
			: actor_base(ai) {}
		void operator()() const
		{
			glNormalPointer(GL_FLOAT,ai.stride,ai.offset);
			glEnableClientState(GL_NORMAL_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling normals on ogl stream failed!");
		}
	};

	class tex_actor : public actor_base {
	public:
		tex_actor(const actor_info& ai)
			: actor_base(ai) {}
		void operator()() const
		{
			glClientActiveTextureARB(GL_TEXTURE0 + ai.index);
			glTexCoordPointer(2,GL_FLOAT,ai.stride,ai.offset);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling texture coordinates on ogl stream failed!");
		}
	};

	class diffuse_actor : public actor_base {
	public:
		diffuse_actor(const actor_info& ai)
			: actor_base(ai) {}
		void operator()() const
		{
  			glColorPointer(4,GL_UNSIGNED_BYTE,ai.stride,ai.offset);
        	        glEnableClientState(GL_COLOR_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling diffuse colors on ogl stream failed!");
		}
	};
}

sge::ogl::vertex_format::vertex_format(const sge::vertex_format& f)
{
	vertex_size offset = 0;
	const sge::vertex_format::usage_list& l = f.elements();

	for(sge::vertex_format::usage_list::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		for(vertex_size count = 0; count < it->count(); ++count)
		{
			const vertex_size cur = offset + count*it->size();
			const actor_info ai(cur, f.stride(), count);
			switch(it->usage()) {
			case VU_Pos:
				actors.push_back(actor_base_ptr(new pos_actor(ai)));
				break;
			case VU_Tex:
				actors.push_back(actor_base_ptr(new tex_actor(ai)));
				break;
			case VU_Normal:
				actors.push_back(actor_base_ptr(new normal_actor(ai)));
				break;
			case VU_Diffuse:
				actors.push_back(actor_base_ptr(new diffuse_actor(ai)));
				break;
			default:
				throw std::runtime_error("unsupported vertex_usage");
			}
		}
		
		oi[it->usage()] = offset;
		offset += it->stride();
	}
}

void sge::ogl::vertex_format::use_me()
{
	glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
	for(actor_array::const_iterator it = actors.begin(); it != actors.end(); ++it)
		(**it)();
}
