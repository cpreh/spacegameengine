#ifndef SGE_OGL_BASIC_ARB_BUFFER_HPP_INCLUDED
#define SGE_OGL_BASIC_ARB_BUFFER_HPP_INCLUDED

#include "./extensions.hpp"
#include "./conversion.hpp"
#include "./error.hpp"

namespace sge
{
	namespace ogl
	{
		template<typename Base, GLenum Type> class basic_arb_buffer : public Base {
		public:
			typedef typename Base::value_type value_type;
			typedef typename Base::size_type size_type;
			typedef typename Base::difference_type difference_type;
			typedef typename Base::pointer pointer;
			typedef typename Base::const_pointer const_pointer;
			typedef typename Base::iterator iterator;
			typedef typename Base::const_iterator const_iterator;
			typedef typename Base::reverse_iterator reverse_iterator;
			typedef typename Base::const_reverse_iterator const_reverse_iterator;
			
			basic_arb_buffer(const size_type sz, const size_type stride, const resource_flag_t flags, const const_pointer src)
				: sz(sz), stride(stride), flags(flags), dest(0)
			{
				glGenBuffersARB(1,&id);
				if(is_error())
					throw std::runtime_error("glGenBuffersARB() failed!");
				_set_size(src);
			}

			~basic_arb_buffer()
			{
				glDeleteBuffersARB(1,&id);
			}

			void lock(const lock_flag_t lockflags)
			{
				if(dest)
					throw std::logic_error("ogl_buffer::lock(), you have to unlock before locking!");
				
				const GLuint glflags = convert_lock_flags(lockflags);
				bind_me();
				dest = static_cast<pointer>(glMapBufferARB(Type,glflags));
				if(is_error())
				{
					dest = 0;
					throw std::runtime_error("glMapBufferARB() failed!");
				}
			}

			void unlock()
			{
				if(!dest)
					throw std::logic_error("ogl_buffer::unlock(), buffer is not locked! cannot unlock!");
				bind_me();
				glUnmapBufferARB(Type);
				dest = 0;
								
				if(is_error())
					throw std::runtime_error("glUnmapBufferARB() failed!");
			}

			void set_data(const const_pointer data, const size_type first, const size_type count)
			{
				if(first + count > size())
					throw std::length_error("ogl_buffer::set_data(), first + count out of range!");
				if(dest)
					throw std::logic_error("ogl_buffer::set_data(), buffer must not be locked!");
				bind_me();
				glBufferSubDataARB(Type,first*stride,count*stride,data);
				if(is_error())
					throw std::runtime_error("glBufferSubDataARB() failed!");
			}

			virtual iterator begin() = 0;
			virtual const_iterator begin() const = 0;
			iterator end() { return begin() + size()*stride; }
			const_iterator end() const { return begin() + size()*stride; }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
			size_type size() const { return sz; }
			resource_flag_t get_flags() const { return flags; }
			
			void resize(const size_type newsize, const const_pointer src)
			{
				if(newsize <= size())
					return;
				if(dest)
					throw std::logic_error("ogl_buffer::resize(), buffer must be unlocked!");
				sz = newsize;
				_set_size(src);
			}

			void restore() {}
			pointer raw_data() { return dest; }
			const_pointer raw_data() const { return dest; }

			void bind_me() const
			{
				glBindBufferARB(Type,id);
				if(is_error())
					throw std::runtime_error("glBindBufferARB() failed!");
			}
		private:
			void _set_size(const const_pointer src)
			{
				const GLuint glflags = convert_resource_flags(flags);
				const size_type nsz = size()*stride;
				bind_me();
				glBufferDataARB(Type,nsz,src,glflags);
				if(is_error())
					throw std::runtime_error("glBufferDataARB() failed!");
			}
			
			struct init_guard {
				init_guard()
				{
					if(!GLEW_ARB_vertex_buffer_object)
						throw std::runtime_error("OpenGL extension not supported: ARB_vertex_buffer_object!");
				}
			};
			init_guard _guard;
			size_type sz;
			size_type stride;
			resource_flag_t flags;
			pointer dest;
			GLuint id;
		};
	}
}

#endif
