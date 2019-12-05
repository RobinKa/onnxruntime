// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// This is the Onnxruntime side of the bridge to allow providers to be built as a DLL
// It implements onnxruntime::ProviderHost

#include "core/framework/data_types.h"
#include "core/framework/allocatormgr.h"
#include "core/providers/mkldnn/mkldnn_provider_factory.h"
#include "core/session/abi_session_options_impl.h"
#include "core/platform/env.h"
#include "core/framework/execution_provider.h"
#include "core/framework/compute_capability.h"
#include "core/providers/shared_library/bridge.h"
#include "core/common/logging/logging.h"
#include "core/common/cpuid_info.h"

using namespace google::protobuf::internal;

// To get the address of the private methods, we use the templated friend trick below:
template <typename PtrType, PtrType Value, typename TagType>
struct private_access_helper {
  friend PtrType private_cast(TagType) {
    return Value;
  }
};

// Then we instantiate the templates for the types we're interested in getting members for.
// Then by calling private_cast(the name of one of the structs{}) it will return a pointer to the private member function
struct private_cast_1 {};
template struct private_access_helper<void (RepeatedPtrFieldBase::*)(int), &RepeatedPtrFieldBase::Reserve, private_cast_1>;
auto private_cast_RepeatedPtrFieldBase_Reserve() { return private_cast(private_cast_1{}); }
struct private_cast_2 {};
template struct private_access_helper<onnx::TensorProto* (*)(google::protobuf::Arena*), &google::protobuf::Arena::CreateMaybeMessage<onnx::TensorProto>, private_cast_2>;
auto private_cast_Arena_CreateMaybeMessage_onnx_TensorProto() { return private_cast(private_cast_2{}); }

namespace onnxruntime {

struct ProviderHostImpl : ProviderHost {
  ProviderHostImpl() {
#if 0
    google_protobuf_internal_RepeatedPtrFieldBase_Reserve = private_cast_RepeatedPtrFieldBase_Reserve();
    google_protobuf_Arena_CreateMaybeMessage_onnx_TensorProto = private_cast_Arena_CreateMaybeMessage_onnx_TensorProto();

    google_protobuf_internal_GetEmptyStringAlreadyInited = &google::protobuf::internal::GetEmptyStringAlreadyInited;
#endif

    DataTypeImpl_GetType_Tensor = &DataTypeImpl::GetType<Tensor>;
    DataTypeImpl_GetType_float = &DataTypeImpl::GetType<float>;
    DataTypeImpl_GetTensorType_float = &DataTypeImpl::GetTensorType<float>;

#if 0
    onnx_AttributeProto_CopyFrom = &onnx::AttributeProto::CopyFrom;
    onnx_TensorProto_CopyFrom = &onnx::TensorProto::CopyFrom;

    onnx_AttributeProto_AttributeType_IsValid = &onnx::AttributeProto_AttributeType_IsValid;
#endif

    //    CreateAllocator = &onnxruntime::CreateAllocator;

#if 0

    CPUIDInfo_GetCPUIDInfo = &CPUIDInfo::GetCPUIDInfo;
    KernelDefBuilder_Provider = &KernelDefBuilder::Provider;
    KernelDefBuilder_SetName = &KernelDefBuilder::SetName;
    KernelDefBuilder_SetDomain = &KernelDefBuilder::SetDomain;
    KernelDefBuilder_TypeConstraint = &KernelDefBuilder::TypeConstraint;
#endif
  }

  logging::Logger*
  LoggingManager_GetDefaultLogger() override {
    return const_cast<logging::Logger*>(&logging::LoggingManager::DefaultLogger());
  }

  void* HeapAllocate(size_t size) override { return new uint8_t[size]; }
  void HeapFree(void* p) override { delete p; }

  const TensorShape& Tensor_Shape(const void* this_) override {
    return reinterpret_cast<const Tensor*>(this_)->Shape();
  }

  void KernelDefBuilder_Provider(void* this_, char const* p1) override {
    reinterpret_cast<KernelDefBuilder*>(this_)->Provider(p1);
  }

  void KernelDefBuilder_SetName(void* this_, char const* p1) override {
    reinterpret_cast<KernelDefBuilder*>(this_)->SetName(p1);
  }

  void KernelDefBuilder_SetDomain(void* this_, char const* p1) override {
    reinterpret_cast<KernelDefBuilder*>(this_)->SetDomain(p1);
  }

  void KernelDefBuilder_TypeConstraint(void* this_, char const* p1, const DataTypeImpl* p2) override {
    reinterpret_cast<KernelDefBuilder*>(this_)->TypeConstraint(p1, p2);
  }

#if 0
  void onnx_AttributeProto_constructor(void* _this) override {
    new (_this) onnx::AttributeProto();
  }

  void onnx_AttributeProto_copy_constructor(void* _this, void* copy) override {
    new (_this) onnx::AttributeProto(*reinterpret_cast<const onnx::AttributeProto*>(copy));
  }

  void onnx_AttributeProto_destructor(void* _this) override {
    reinterpret_cast<onnx::AttributeProto*>(_this)->AttributeProto::~AttributeProto();
  }

  void onnxruntime_Status_constructor_1(void* _this, const void* category, int code, char const* msg) override {
    new (_this) Status(*reinterpret_cast<const StatusCategory*>(category), code, msg);
  }

  void onnxruntime_Status_constructor_2(void* _this, const void* category, int code, const void* std_string_msg) override {
    new (_this) Status(*reinterpret_cast<const StatusCategory*>(category), code, *reinterpret_cast<const std::string*>(std_string_msg));
  }

  void onnxruntime_OpKernelInfo_copy_constructor(void* _this, void* p1) override {
    new (_this) OpKernelInfo(*reinterpret_cast<const OpKernelInfo*>(p1));
  }

  void onnxruntime_OpKernelInfo_constructor(void* _this, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) override {
    new (_this) OpKernelInfo(*reinterpret_cast<const onnxruntime::Node*>(p1),
                             *reinterpret_cast<const KernelDef*>(p2),
                             *reinterpret_cast<const IExecutionProvider*>(p3),
                             *reinterpret_cast<const std::unordered_map<int, OrtValue>*>(p4),
                             *reinterpret_cast<const OrtValueNameIdxMap*>(p5),
                             *reinterpret_cast<const FuncManager*>(p6),
                             *reinterpret_cast<const DataTransferManager*>(p7));
  }
#endif

  void LogRuntimeError(uint32_t session_id, const common::Status& status, const char* file, const char* function, uint32_t line) override {
    return ::onnxruntime::LogRuntimeError(session_id, status, file, function, line);
  }

#if 0
  void* CPUAllocator_Alloc(CPUAllocator* _this, uint64_t p1) override {
    return _this->CPUAllocator::Alloc(p1);
  }

  void CPUAllocator_Free(CPUAllocator* _this, void* p1) override {
    return _this->CPUAllocator::Free(p1);
  }

  const OrtMemoryInfo& CPUAllocator_Info(const CPUAllocator* _this) override {
    return _this->CPUAllocator::Info();
  }

  int GraphViewer_MaxNodeIndex(const GraphViewer* _this) override {
    return _this->MaxNodeIndex();
  }

  const std::string& GraphViewer_Name(const GraphViewer* _this) override {
    return _this->Name();
  }

  const Node* GraphViewer_GetNode(const GraphViewer* _this, NodeIndex p1) override {
    return _this->GetNode(p1);
  }

  const InitializedTensorSet& GraphViewer_GetAllInitializedTensors(const GraphViewer* _this) override {
    return _this->GetAllInitializedTensors();
  }

  std::vector<std::unique_ptr<ComputeCapability>> IExecutionProvider_GetCapability(const IExecutionProvider* _this, const GraphViewer& p1, const std::vector<const KernelRegistry*>& p2) override {
    return _this->IExecutionProvider::GetCapability(p1, p2);
  }

  std::shared_ptr<IAllocator> IExecutionProvider_GetAllocator(const IExecutionProvider* _this, int p1, OrtMemType p2) override {
    return _this->IExecutionProvider::GetAllocator(p1, p2);
  }

  void IExecutionProvider_InsertAllocator(IExecutionProvider* _this, std::shared_ptr<IAllocator> p1) override {
    _this->IExecutionProvider::InsertAllocator(std::move(p1));
  }

  Status IExecutionProvider_OnRunEnd(IExecutionProvider* _this) override {
    return _this->IExecutionProvider::OnRunEnd();
  }

  Status IExecutionProvider_OnRunStart(IExecutionProvider* _this) override {
    return _this->IExecutionProvider::OnRunStart();
  }

  Status KernelRegistry_Register(KernelRegistry* _this, KernelCreateInfo&& p1) override {
    return _this->KernelRegistry::Register(std::move(p1));
  }

  NodeIndex Node_Index(const Node* _this) override {
    return _this->Node::Index();
  }

  const NodeAttributes& Node_GetAttributes(const Node* _this) override {
    return _this->Node::GetAttributes();
  }

  const ONNX_NAMESPACE::OpSchema* Node_Op(const Node* _this) override {
    return _this->Node::Op();
  }

  const std::string& Node_OpType(const Node* _this) override {
    return _this->Node::OpType();
  }

  void onnxruntime_Node_NodeConstIterator_constructor(void* _this, void* p1) override {
    new (_this) Node::NodeConstIterator(*reinterpret_cast<Node::EdgeConstIterator*>(p1));
  }

  bool Node_NodeConstIterator_operator_not_equal(const void* _this, const void* p1) {
    return reinterpret_cast<const Node::NodeConstIterator*>(_this)->operator!=(*reinterpret_cast<const Node::NodeConstIterator*>(p1));
  }

  void Node_NodeConstIterator_operator_plusplus(void* _this) {
    reinterpret_cast<Node::NodeConstIterator*>(_this)->operator++();
  }

  const Node& Node_NodeConstIterator_operator_star(const void* _this) {
    return reinterpret_cast<const Node::NodeConstIterator*>(_this)->operator*();
  }

  const std::string& NodeArg_Name(const NodeArg* _this) override {
    return _this->NodeArg::Name();
  }

  const ONNX_NAMESPACE::TensorShapeProto* NodeArg_Shape(const NodeArg* _this) override {
    return _this->NodeArg::Shape();
  }

  ONNX_NAMESPACE::DataType NodeArg_Type(const NodeArg* _this) override {
    return _this->NodeArg::Type();
  }

  void onnxruntime_TensorShape_constructor(void* _this, int64_t const* p1, uint64_t p2) override {
    new (_this) TensorShape(p1, p2);
  }
#endif

  void* TensorShape_TensorShape(const std::initializer_list<int64_t>& dims) override {
    return new TensorShape(dims);
  }

  int64_t TensorShape_Size(const void* _this) override {
    return reinterpret_cast<TensorShape*>(_this)->Size();
  }

  void* TensorShape_Slice(const TensorShape* _this, uint64_t p1) override {
    return reinterpret_cast<TensorShape*>(_this)->Slice(p1);
  }

} provider_host_;

std::shared_ptr<IExecutionProviderFactory> CreateExecutionProviderFactory_Mkldnn(int device_id) {
  void* handle;
  Env::Default().LoadDynamicLibrary("C:\\code\\github\\onnxrt\\build\\windows\\debug\\debug\\onnxruntime_providers_mkldnn.dll", &handle);
  if (!handle)
    return nullptr;

  Provider* (*PGetProvider)();

  Env::Default().GetSymbolFromLibrary(handle, "GetProvider", (void**)&PGetProvider);
  //return std::make_shared<onnxruntime::MkldnnProviderFactory>(device_id);
  //TODO: This is apparently a bug. The consructor parameter is create-arena-flag, not the device-id

  Provider* provider = PGetProvider();
  provider->SetProviderHost(provider_host_);

  return provider->CreateExecutionProviderFactory(device_id);
}

}  // namespace onnxruntime

ORT_API_STATUS_IMPL(OrtSessionOptionsAppendExecutionProvider_Mkldnn, _In_ OrtSessionOptions* options, int use_arena) {
  options->provider_factories.push_back(onnxruntime::CreateExecutionProviderFactory_Mkldnn(use_arena));
  return nullptr;
}
