#ifndef SGE_OGL_CONVERSION_HPP_INCLUDED
#define SGE_OGL_CONVERSION_HPP_INCLUDED

#include "../../core/renderer/renderer_types.hpp"
#include "./extensions.hpp"

namespace sge
{
namespace ogl
{

template<typename D, typename S> D convert_cast(const S&);
template<> GLenum convert_cast(const primitive_type& t);
template<> GLenum convert_cast(const bool_state& b);
template<> GLenum convert_cast(const filter_arg& a);
template<> GLenum convert_cast(const filter_arg_value& av);
template<> GLenum convert_cast(const matrix_usage& u);
GLuint convert_lock_flags(lock_flag_t f);
GLuint convert_resource_flags(resource_flag_t t);

}
}

#endif

