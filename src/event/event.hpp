#pragma once


enum class EventType {
    None,
    ToggleWheel, 
    WheelSelected, 
    ToggleUI, 
};

struct Event {
    virtual EventType getType() const = 0;
    virtual ~Event() = default;
};

struct WheelSelectedEvent : Event {
    EventType getType() const override {
        return EventType::WheelSelected;
    }

    int wheelIdx;
    WheelSelectedEvent(int idx): wheelIdx(idx) {};
};

struct ToggleWheelEvent : Event {
    EventType getType() const override {
        return EventType::ToggleWheel;
    }
    bool visible;
    ToggleWheelEvent(bool visible): visible(visible) {};
};

struct ToggleUIEvent : Event {
    EventType getType() const override {
        return EventType::ToggleUI;
    }
    ToggleUIEvent() = default;
};