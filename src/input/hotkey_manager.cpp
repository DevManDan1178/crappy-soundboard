#include "input/hotkey_manager.hpp"
#include "SDL.h"
#include "event/event_dispatcher.hpp"
#include <functional>
#include <iostream>

const std::function onOpenWheelHotkeyPressed = []() -> void {
    std::cout << "open wheel hotkey pressed" << std::endl;
    EventDispatcher::Emit(ToggleWheelEvent(true));
};

const std::function onOpenWheelHotkeyReleased = []() -> void {
    EventDispatcher::Emit(ToggleWheelEvent(false));
};



bool HotkeyManager::SetOpenWheelHotkey(Hotkey hotkey) {
    //Check if it conflicts with other hotkeys (currently no other hotkeys)
    Hotkey& previousHotkey = openWheelHotkey;   
    openWheelHotkey = hotkey;
    
    std::cout << "Set open wheel hotkey" << std::endl;
    InputListener::SetOnHotkeyPress(hotkey, onOpenWheelHotkeyPressed);
    InputListener::SetOnHotkeyRelease(previousHotkey, onOpenWheelHotkeyReleased);
    return true;
}