#include "../../../core/main/algorithm.hpp"
#include "../../../core/renderer/lock_ptr.hpp"
#include "../index_buffer.hpp"
#include "../conversion.hpp"

sge::d3d::index_buffer::index_buffer(renderer* const r, d3d_device_ptr device, const size_type sz, const resource_flag_t nflags, const const_pointer src)
: resource(r, nflags & RF_Dynamic),
  device(device), buffer(0), _flags(nflags), sz(sz), lock_dest(0)
{
	init(src);
}

void sge::d3d::index_buffer::init(const const_pointer src)
{
	const D3DFORMAT format = D3DFMT_INDEX16;
	const DWORD usage = convert_cast<DWORD>(flags);
	const D3DPOOL pool = convert_cast<D3DPOOL>(flags);

	IDirect3DIndexBuffer9* p;
	if(device->CreateIndexBuffer(static_cast<unsigned>(sz * stride), usage, format, pool, &p,0) != D3D_OK)
		throw std::runtime_error("cannot create index buffer");
	buffer = p;

	if(src)
	{
		lock_ptr<index_buffer> l(this);
		copy(src,src+size(),lock_dest);
	}
}

sge::d3d::index_buffer::iterator sge::d3d::index_buffer::begin()
{
	return iterator(lock_dest);
}

sge::d3d::index_buffer::const_iterator sge::d3d::index_buffer::begin() const
{
	return const_iterator(lock_dest);
}

sge::d3d::index_buffer::iterator sge::d3d::index_buffer::end()
{
	return iterator(lock_dest + size());
}

sge::d3d::index_buffer::const_iterator sge::d3d::index_buffer::end() const
{
	return const_iterator(lock_dest + size());
}

sge::d3d::index_buffer::reverse_iterator sge::d3d::index_buffer::rbegin()
{
	return reverse_iterator(end());
}

sge::d3d::index_buffer::const_reverse_iterator sge::d3d::index_buffer::rbegin() const
{
	return const_reverse_iterator(end());
}

sge::d3d::index_buffer::reverse_iterator sge::d3d::index_buffer::rend()
{
	return reverse_iterator(begin());
}

sge::d3d::index_buffer::const_reverse_iterator sge::d3d::index_buffer::rend() const
{
	return const_reverse_iterator(begin());
}

void sge::d3d::index_buffer::lock(const lock_flag_t flags, const size_type first, const size_type count)
{
	if(lock_dest)
		throw std::logic_error("d3d::index_buffer::lock() you have to unlock first!");
	void* p = 0;
	const DWORD lflags = convert_lock_flags(flags,flags);
	if(buffer->Lock(first*stride,count*stride,&p,lflags) != D3D_OK)
		throw std::runtime_error("cannot lock index buffer");
	lock_dest = static_cast<pointer>(p);
}

void sge::d3d::index_buffer::unlock()
{
	if(!lock_dest)
		throw std::logic_error("d3d::index_buffer::unlock() you have to lock first!");
	if(buffer->Unlock() != D3D_OK)
		throw std::runtime_error("cannot unlock index buffer");
	lock_dest = 0;
}

sge::d3d::index_buffer::size_type sge::d3d::index_buffer::size() const
{
	return sz;
}

sge::resource_flag_t sge::d3d::index_buffer::flags() const
{
	return _flags;
}

void sge::d3d::index_buffer::resize(const size_type newsize)
{
	if(lock_dest)
		throw std::logic_error("d3d::index_buffer::resize() you have to unlock before resizing");

	sz = newsize;
	init();
}

void sge::d3d::index_buffer::on_loss()
{
	buffer = 0;
}

void sge::d3d::index_buffer::on_reset()
{
	init();
}

sge::d3d::index_buffer::pointer sge::d3d::index_buffer::data()
{
	return lock_dest;
}

sge::d3d::index_buffer::const_pointer sge::d3d::index_buffer::data() const
{
	return lock_dest;
}
