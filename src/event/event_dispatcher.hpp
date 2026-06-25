#pragma once
#include <unordered_set>
#include <functional>
#include "event/event.hpp"

using EventListener = std::function<void(const Event&)>;
namespace EventDispatcher {
/**
 * @brief Adds a listener to the dispatcher
 * @param listener listener function to call on every event
 * @return the ID of the listener's connection
 */
int Subscribe(const EventListener& listener);

/**
 * @brief Removes a listener from the  dispatcher
 * @param connectionId the ID of the listener's connection
 */
void Unsubscribe(int connectionId);

/**
 * @brief Calls every subscribed listener with the event
 * @param event the event to call with
 */
void Emit(const Event& event);

};