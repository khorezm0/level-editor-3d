#include <iostream>
#include "InputSystem.h"

int inited=0;

// Define your user buttons
enum Button
{
	ButtonMenu,
	MouseLeftButton,
	MouseX,
	MouseY
};

gainput::InputManager* inputs_manager;
gainput::InputMap* inputs_map;

void initInputs(int wndWidth, int wndHeight) 
{
	gainput::InputManager manager;
	manager.SetDisplaySize(wndWidth, wndHeight);
	gainput::DeviceId mouseId = manager.CreateDevice<gainput::InputDeviceMouse>();
	gainput::DeviceId keyboardId = manager.CreateDevice<gainput::InputDeviceKeyboard>();
	gainput::DeviceId padId = manager.CreateDevice<gainput::InputDevicePad>();

	gainput::InputMap map(manager);
	map.MapBool(ButtonMenu, keyboardId, gainput::KeyEscape);
	map.MapBool(MouseLeftButton, mouseId, gainput::MouseButtonLeft);
	map.MapFloat(MouseX, mouseId, gainput::MouseAxisX);
	map.MapFloat(MouseY, mouseId, gainput::MouseAxisY);
	
	inputs_manager = &manager;
	inputs_map = &map;
}

void testInputs()
{
	if (!inited) {
		return;
	}
	inputs_manager->Update();

}
