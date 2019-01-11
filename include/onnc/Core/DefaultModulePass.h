//===- DefaultModulePass.h -------------------------------------------------------===//
//
//                             The ONNC Project
//
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#ifndef ONNC_CORE_DEFAULT_MODULE_PASS_H
#define ONNC_CORE_DEFAULT_MODULE_PASS_H
#include <onnc/Core/ModulePass.h>

#include <type_traits>
#include <utility>

namespace onnc {

/** \class onnc::DefaultModulePass
 *  \brief default module class which implements most of the pure virtual methods
 */
template <
  typename PassType,
  typename ParentType = ModulePass,
  typename = typename std::enable_if<
    std::is_class<PassType>::value
    && std::is_base_of<ModulePass, ParentType>::value
  >::type
>
class DefaultModulePass : public ParentType
                        , public GenerateDefaultPassIdFor<PassType>
{
public:
  using BaseType = DefaultModulePass;

  template <typename... Args>
  DefaultModulePass(Args&&... args)
    : ParentType(std::forward<Args>(args)...)
  { }

  virtual ~DefaultModulePass() = default;
};

} // namespace of onnc

#endif
