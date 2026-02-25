#pragma once

#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief Events that can be observed in the game.
 */
enum class EventType {
    CombatLog,
    GameLog,
    Warning,
    Error,
    Info
};

/**
 * @brief Observer interface for receiving game events.
 * 
 * Part of the Observer pattern to decouple event generation (like taking damage)
 * from event presentation (like logging to console or UI).
 */
class IObserver {
public:
    virtual ~IObserver() = default;
    
    /**
     * @brief Called when a generic event occurs.
     * 
     * @param type The type of the event Notification
     * @param message Text payload of the event
     */
    virtual void onEvent(EventType type, const std::string& message) = 0;
};

/**
 * @brief Subject interface that publishers must inherit from.
 */
class ISubject {
protected:
    std::vector<IObserver*> observers;
    /**
     * @brief Notifies all attached observers of an event.
     */
    void notifyObservers(EventType type, const std::string& message) {
        for (auto observer : observers) {
            observer->onEvent(type, message);
        }
    }

public:
    virtual ~ISubject() = default;
    
    /**
     * @brief Attaches a new observer to the subject.
     */
    void addObserver(IObserver* observer) {
        if (observer && std::find(observers.begin(), observers.end(), observer) == observers.end()) {
            observers.push_back(observer);
        }
    }
    
    /**
     * @brief Detaches an observer.
     */
    void removeObserver(IObserver* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
};
