/* Copyright Amazon Web Services and its Affiliates. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_NEURON_RUNTIME_DIRECT_PROFILER_CONTEXT_H_
#define TENSORFLOW_NEURON_RUNTIME_DIRECT_PROFILER_CONTEXT_H_

#include "adaptor.h"
#include "../macros.h"
#include "tensorflow/core/lib/core/stringpiece.h"

namespace tensorflow {
namespace neuron {
class ProfilerContext {
 public:
  ProfilerContext(const NrtModel& model, std::string profile_dir,
                  const StringPiece& executable);
  ProfilerContext();
  ~ProfilerContext();
  const char* get_path_to_profile_file();
  TFN_DISALLOW_COPY_MOVE_ASSIGN(ProfilerContext);

 private:
  NrtModel model_;
  std::string path_to_profile_file_;
  Status status_;

};
}  // namespace neuron
}  // namespace tensorflow

#endif