#ifndef SGE_D3D_INDEX_BUFFER_HPP_INCLUDED
#define SGE_D3D_INDEX_BUFFER_HPP_INCLUDED

#include "../../core/renderer/index_buffer.hpp"
#include "./resource.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class renderer;

class index_buffer : public sge::index_buffer, public resource {
	friend class renderer;
public:
	index_buffer(renderer* r, d3d_device_ptr device, size_type size, resource_flag_t flags, const_pointer src);
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
	void lock(lock_flag_t flags, size_type first, size_type count);
	void unlock();
	resource_flag_t flags() const;
	pointer data();
	const_pointer data() const;
private:
	void on_loss();
	void on_reset();

	void init(const_pointer src = 0);

	d3d_device_ptr       device;
	d3d_index_buffer_ptr buffer;
	resource_flag_t      _flags;
	size_type            sz;
	pointer              lock_dest;
};

}
}

#endif
