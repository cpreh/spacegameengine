#include "../../../core/main/util.hpp"
#include "../input_device.hpp"
#include <stdexcept>

const DWORD sge::dinput::input_device::coop_level(DISCL_FOREGROUND | DISCL_EXCLUSIVE);
const DIPROPDWORD sge::dinput::input_device::buffer_settings = {
	sizeof(DIPROPDWORD),
	sizeof(DIPROPHEADER),
	0,
	DIPH_DEVICE,
	buffer_size
};

sge::dinput::input_device::input_device(dinput_ptr di, const std::string& name, GUID guid, unsigned index, HWND wnd)
: index(index), name(name)
{
	IDirectInputDevice8* d;
	if(di->CreateDevice(guid,&d,0) != DI_OK)
		throw std::runtime_error("cannot create input device");
	device.reset(d);
	set_cooperative_level(wnd,coop_level);
	set_property(DIPROP_BUFFERSIZE,&buffer_settings.diph);
}

void sge::dinput::input_device::set_cooperative_level(const HWND hwnd, const DWORD flags)
{
	if(device->SetCooperativeLevel(hwnd,flags) != DI_OK)
		throw std::runtime_error("SetCooperativeLevel() failed");
}

void sge::dinput::input_device::set_data_format(const LPCDIDATAFORMAT df)
{
	if(device->SetDataFormat(df) != DI_OK)
		throw std::runtime_error("SetDataFormat() failed");
}

void sge::dinput::input_device::set_property(const REFGUID guid, const LPCDIPROPHEADER diph)
{
	if(device->SetProperty(guid,diph) != DI_OK)
		throw std::runtime_error("SetProperty() failed");
}

void sge::dinput::input_device::acquire()
{
	const HRESULT res = device->Acquire();
	switch(res) {
	case S_FALSE:
	case DI_OK:
		break;
	case DIERR_OTHERAPPHASPRIO:
		break;
	default:
		throw std::runtime_error("Acquire() failed");
	}
	while(device->Acquire() == DIERR_OTHERAPPHASPRIO)
		sge::sleep(10);
}

void sge::dinput::input_device::poll()
{
	if(device->Poll() != DI_OK)
		throw std::runtime_error("Poll() failed");
}

bool sge::dinput::input_device::_get_input(input_buffer data, DWORD& elements)
{
	elements = sizeof(input_buffer) / sizeof(DIDEVICEOBJECTDATA);
	const HRESULT res = device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
	                                            data,
	                                            &elements,
	                                            0);
	switch(res) {
	case DI_OK:
	case DI_BUFFEROVERFLOW:
		return true;
	case DIERR_INPUTLOST:
		acquire();
		return _get_input(data,elements);
	case DIERR_NOTACQUIRED:
		acquire();
		return false;
	default:
		throw std::runtime_error("GetDeviceData() failed");
	}
}

void sge::dinput::input_device::enum_objects(LPDIENUMDEVICEOBJECTSCALLBACK fun)
{
	if(device->EnumObjects(fun,this,DIDFT_ALL) != DI_OK)
		throw std::runtime_error("enumerating objects failed");
}
