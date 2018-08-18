/**
 *  @note This file is part of Empirical, https://github.com/devosoft/Empirical
 *  @copyright Copyright (C) Michigan State University, MIT Software license; see doc/LICENSE.md
 *  @date 2018
 *
 *  @file  types.h
 *  @brief Manipulation tools to quickly identify MABE-specific types.
 */

#ifndef MABE_TYPES_H
#define MABE_TYPES_H

#include <string>

#include "base/Ptr.h"
#include "base/vector.h"
#include "meta/TypePack.h"
#include "tools/GenericFunction.h"

#include "../core/BrainBase.h"
#include "../core/EnvironmentBase.h"
#include "../core/GenomeBase.h"
#include "../core/OrganismBase.h"
#include "../core/OrganismTypeBase.h"
#include "../core/SchemaBase.h"

namespace mabe {

  /// Details about a generic function being passed between OrganismTypes and Environments.
  struct FunctionInfo {
    using fun_ptr_t = emp::Ptr<emp::GenericFunction>;
    size_t id;          ///< Unique ID for this type of function.
    fun_ptr_t fun_ptr;  ///< Pointer to generic function to be called.
    std::string type;   ///< A string representation of the C++ type of this function.
    std::string name;   ///< Unique name for this function.
    std::string desc;   ///< Full description for what this function does.
  };

  template <typename T> using is_module        = std::is_base_of<ModuleBase, T>;

  template <typename T> using is_genome        = std::is_base_of<GenomeBase, T>;
  template <typename T> using is_brain         = std::is_base_of<BrainBase, T>;

  template <typename T> using is_environment   = std::is_base_of<EnvironmentBase, T>;
  template <typename T> using is_organism_type = std::is_base_of<OrganismTypeBase, T>;
  template <typename T> using is_schema        = std::is_base_of<SchemaBase, T>;

  const EnvironmentBase & ToModule(const EnvironmentBase & module) { return module; }
  const OrganismTypeBase & ToModule(const OrganismTypeBase & module) { return module; }
  const SchemaBase & ToModule(const SchemaBase & module) { return module; }

  template <typename T>
  using to_module_t = std::decay_t<decltype(ToModule(*((T*) nullptr)))>;
}

#endif

