// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sampgdk/wrapper.h>

#include "wrapperimpl.h"

namespace sampgdk {

Wrapper::Wrapper() {
    pimpl_ = new WrapperImpl;
}

Wrapper::~Wrapper() {
    delete pimpl_;
}

Wrapper *Wrapper::GetInstance() {
    static Wrapper w;
    return &w;
}

void Wrapper::Initialize(void **ppPluginData) {
    pimpl_->Initialize(ppPluginData);
}

void Wrapper::SetNative(const char *name, AMX_NATIVE native) {
    pimpl_->SetNative(name, native);
}

AMX_NATIVE Wrapper::GetNative(const char *name) const {
    return pimpl_->GetNative(name);
}

void Wrapper::SetPublicHook(const char *name, PublicHandler handler, cell badReturn) {
    pimpl_->SetPublicHook(name, PublicHook(handler, badReturn));
}

bool Wrapper::ExecutePublicHook(AMX *amx, cell *retval, const char *name) const {
    return pimpl_->ExecutePublicHook(amx, retval, name);
}

} // namespace sampgdk

