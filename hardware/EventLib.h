
// This file is largely based on InstLib.h.
// This file maintains information about events available in virtual hardware.

#ifndef EMP_EVENT_LIB_H
#define EMP_EVENT_LIB_H

#include <functional>
#include <unordered_set>
#include <map>
#include <string>
#include <iostream>

#include "../tools/FunctionSet.h"
#include "../tools/map_utils.h"
#include "../base/vector.h"

namespace emp {

  template<typename HARDWARE_T>
  class EventLib {
  public:
    using hardware_t = HARDWARE_T;
    using event_t = typename hardware_t::event_t;
    using fun_t = std::function<void(hardware_t &, const event_t &)>;
    using properties_t = std::unordered_set<std::string>;
    using fun_set_t = FunctionSet<void(hardware_t &, const event_t &)>;

    struct EventDef {
      std::string name;         // Name of this event.
      fun_t handler;            // Function to call to handle this event.
      std::string desc;         // Description of event.
      properties_t properties;  // Any properties that should be associated with this type of event.
      fun_set_t dispatch_funs;     // Functions to call when this type of event is triggered.

      EventDef(const std::string & _n, fun_t _handler, const std::string & _d,
        const properties_t & _properties)
        : name(_n), handler(_handler), desc(_d), properties(_properties),
          dispatch_funs() { ; }
      EventDef(const EventDef &) = default;
    };

  protected:
    emp::vector<EventDef> event_lib;                // Full definitions of each event.
    std::map<std::string, size_t> name_map;         // Event name -> ID map.


  public:
    EventLib() : event_lib(), name_map() { ; }
    EventLib(const EventLib &) = default;
    ~EventLib() { ; }

    EventLib & operator=(const EventLib &) = default;
    EventLib & operator=(EventLib &&) = default;

    const std::string & GetName(size_t id) const { return event_lib[id].name; }
    const fun_t & GetHandler(size_t id) const { return event_lib[id].handler; }
    const fun_set_t & GetDispatchFuns(size_t id) const { return event_lib[id].dispatch_funs; }
    const std::string & GetDesc(size_t id) const { return event_lib[id].desc; }
    const properties_t & GetProperties(size_t id) const { return event_lib[id].properties; }
    bool HasProperty(size_t id, std::string property) const { return event_lib[id].properties.count(property); }
    size_t GetSize() const { return event_lib.size(); }

    size_t GetID(const std::string & name) const {
      emp_assert(Has(name_map, name), name);
      return Find(name_map, name, (size_t)-1);
    }

    /// Add a new event to the event library.
    void AddEvent(const std::string & name,
                  const fun_t & handler_fun,
                  const std::string & desc="",
                  const properties_t & event_properties=properties_t())
    {
      const size_t id = event_lib.size();
      event_lib.emplace_back(name, handler_fun, desc, event_properties);
      name_map[name] = id;
    }

    /// Register a dispatch function for event specified by id.
    void RegisterDispatchFun(size_t id, fun_t dispatch_fun) {
      event_lib[id].dispatch_funs.Add(dispatch_fun);
    }
    void RegisterDispatchFun(const std::string & name, fun_t dispatch_fun) {
      event_lib[GetID(name)].dispatch_funs.Add(dispatch_fun);
    }

    /// Trigger event.
    void TriggerEvent(hardware_t & hw, const event_t & event) const {
      event_lib[event.id].dispatch_funs.Run(hw, event);
    }

    /// Handle event.
    void HandleEvent(hardware_t & hw, const event_t & event) const {
      event_lib[event.id].handler(hw, event);
    }

  };

}

#endif
