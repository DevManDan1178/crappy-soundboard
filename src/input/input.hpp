#pragma once
#include "SDL.h"
#include <unordered_map>
#include "input/hotkeys.hpp"

namespace Input {

    /**
     * @brief queries for a hotkey input, suspending all other input detection. (Use for changing hotkeys in UI)
     * @return the hotkey obtained
     */
    Hotkey queryHotkey();
    
    /**
     * @brief gets the current state of modifier inputs
     * @return Modifiers object of the current state of modifier inputs
     */
    Modifiers& getModifierState();

    /**
     * @brief parses the SDL scancode into a keycode
     * @return the corresponding keycode (uiohook)
     */
    int ParseSDLScancode(const SDL_Scancode& scanCode);
    
    /**
     * @brief checks if the SDL_Scancode is invalid
     * @return if the scancode is invalid
     */
    bool IsScancodeInvalid(const SDL_Scancode& scanCode);
    
    inline const std::unordered_map<SDL_Keymod, Modifiers> HOTKEY_MODIFIERS = {
        {KMOD_SHIFT, Modifiers::Shift},
        {KMOD_CTRL, Modifiers::Ctrl},
        {KMOD_ALT, Modifiers::Alt}
    };
};