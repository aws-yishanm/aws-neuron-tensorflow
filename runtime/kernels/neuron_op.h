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

#ifndef TENSORFLOW_NEURON_RUNTIME_KERNELS_NEURON_OP_H_
#define TENSORFLOW_NEURON_RUNTIME_KERNELS_NEURON_OP_H_

#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "../macros.h"
#include "../device.h"


namespace tensorflow {
namespace neuron {


class NeuronOp : public OpKernel {
public:
    explicit NeuronOp(OpKernelConstruction *ctx);
    void Compute(OpKernelContext *ctx) override;
    ~NeuronOp() override;

private:
    Status initialize(const std::string &session_handle);
    Status check_input_tensors(const std::vector<const Tensor*> &input_tensors);
    tensorflow::mutex mutex_model_;
    NeuronDevice *neuron_device_ = nullptr;
    uint32_t nn_id_ = NRT_INVALID_NN_ID;
    std::vector<size_t> input_tensor_sizes_;
    std::vector<size_t> output_tensor_sizes_;
    uint32_t max_num_infers_ = 5;
    static const int64 INFER_SEM_MAX_CAPACITY = 2048;
    xla::Semaphore infer_sem_;
    std::shared_ptr<xla::Semaphore::ScopedReservation> infer_sem_reserve_ptr_ = nullptr;
    ProfilerInterface profile_;
    uint64 last_infer_timestamp_ = 0;
    static const uint64 INFER_NEED_PING_MICROSEC_ = 1024 * 1024;
};


}  // namespace neuron
}  // namespace tensorflow

#endif  // TENSORFLOW_NEURON_RUNTIME_KERNELS_NEURON_OP_H_
