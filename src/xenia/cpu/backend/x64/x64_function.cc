/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/cpu/backend/x64/x64_function.h"

#include "xenia/cpu/backend/x64/x64_backend.h"
#include "xenia/cpu/runtime.h"
#include "xenia/cpu/thread_state.h"

namespace xe {
namespace cpu {
namespace backend {
namespace x64 {

X64Function::X64Function(FunctionInfo* symbol_info)
    : Function(symbol_info), machine_code_(nullptr), code_size_(0) {}

X64Function::~X64Function() {
  // machine_code_ is freed by code cache.
}

void X64Function::Setup(void* machine_code, size_t code_size) {
  machine_code_ = machine_code;
  code_size_ = code_size;
}

int X64Function::AddBreakpointImpl(Breakpoint* breakpoint) { return 0; }

int X64Function::RemoveBreakpointImpl(Breakpoint* breakpoint) { return 0; }

int X64Function::CallImpl(ThreadState* thread_state, uint32_t return_address) {
  auto backend = (X64Backend*)thread_state->runtime()->backend();
  auto thunk = backend->host_to_guest_thunk();
  thunk(machine_code_, thread_state->context(),
        reinterpret_cast<void*>(uintptr_t(return_address)));
  return 0;
}

}  // namespace x64
}  // namespace backend
}  // namespace cpu
}  // namespace xe
