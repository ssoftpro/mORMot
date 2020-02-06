#ifndef SynSM_h
#define SynSM_h

#ifdef _WIN32
  #define WIN32 // JS_PUBLIC_API -> MOZ_EXPORT definition checks for WIN32 in some situations, without leading undescore
#endif

#include <jsapi.h>
#include <jsfriendapi.h>
#include <js/Initialization.h>
#include <js/ArrayBuffer.h>  // JS::{NewArrayBuffer,IsArrayBufferObject,GetArrayBuffer{ByteLength,Data}}
#include <js/SharedArrayBuffer.h>  // JS::{NewSharedArrayBuffer,GetSharedArrayBufferData}
#include <js/Date.h>
#include <js/CompilationAndEvaluation.h>
#include <js/ContextOptions.h>
#include <js/Warnings.h>
#include <js/JSON.h>

extern "C" {
	JS_PUBLIC_API bool (*SM_Initialize)(void) = &JS_Init;

    JS_PUBLIC_API void SM_DisableExtraThreads(void);

    JS_PUBLIC_API void (*SM_ShutDown)(void) = &JS_ShutDown;

    JS_PUBLIC_API int64_t (*SM_Now)(void) = &JS_Now;

    JS_PUBLIC_API JSString* (*SM_GetEmptyString)(JSContext* cx) = &JS_GetEmptyString;

    JS_PUBLIC_API JSType (*SM_TypeOfValue)(JSContext* cx, JS::Handle<JS::Value> v) = &JS_TypeOfValue;

    //JS_PUBLIC_API void (*SM_BeginRequest)(JSContext* cx) = &JS_BeginRequest; -- removed in esr60/68

    //JS_PUBLIC_API void (*SM_EndRequest)(JSContext* cx) = &JS_EndRequest; -- removed in esr60/68

    JS_PUBLIC_API JSContext* (*SM_NewContext)(
        uint32_t maxbytes, uint32_t maxNurseryBytes, JSRuntime* parentRuntime) = &JS_NewContext;

    JS_PUBLIC_API bool (*SM_InitSelfHostedCode)(JSContext* cx) = &JS::InitSelfHostedCode;

    JS_PUBLIC_API void (*SM_DestroyContext)(JSContext* cx) = &JS_DestroyContext;

    JS_PUBLIC_API void* (*SM_GetContextPrivate)(JSContext* cx) = &JS_GetContextPrivate;

    JS_PUBLIC_API void (*SM_SetContextPrivate)(JSContext* cx, void* data) = &JS_SetContextPrivate;

    JS_PUBLIC_API bool (*SM_WrapObject)(JSContext* cx, JS::MutableHandleObject objp) = &JS_WrapObject;

    JS_PUBLIC_API JS::Realm* (*SM_EnterRealm)(JSContext* cx, JSObject* target) = &JS::EnterRealm;

    JS_PUBLIC_API void (*SM_LeaveRealm)(JSContext* cx, JS::Realm* oldRealm) = &JS::LeaveRealm;

    JS_PUBLIC_API bool (*SM_InitRealmStandardClasses)(JSContext* cx/*, JS::Handle<JSObject*> obj*/) = &JS::InitRealmStandardClasses;

    JS_PUBLIC_API JSObject* (*SM_CurrentGlobalOrNull)(JSContext* cx) = &JS::CurrentGlobalOrNull;

    JS_PUBLIC_API bool (*SM_InitReflectParse)(JSContext* cx, JS::HandleObject global) = &JS_InitReflectParse;

#ifdef JS_HAS_CTYPES
    JS_PUBLIC_API bool (*SM_InitCTypesClass)(JSContext* cx, JS::HandleObject global) = &JS_InitCTypesClass;
#endif

    JS_PUBLIC_API bool (*SM_DefineDebuggerObject)(JSContext* cx, JS::HandleObject obj) = &JS_DefineDebuggerObject;

    JS_PUBLIC_API void (*SM_GC)(JSContext* cx, JS::GCReason reason) = &JS_GC;

    JS_PUBLIC_API void (*SM_MaybeGC)(JSContext* cx) = &JS_MaybeGC;

    JS_PUBLIC_API void (*SM_SetGCParameter)(JSContext* cx, JSGCParamKey key, uint32_t value) = &JS_SetGCParameter;

    JS_PUBLIC_API uint32_t (*SM_GetGCParameter)(JSContext* cx, JSGCParamKey key) = &JS_GetGCParameter;

    JS_PUBLIC_API void (*SM_SetGCParametersBasedOnAvailableMemory)(JSContext* cx, uint32_t availMem) = &JS_SetGCParametersBasedOnAvailableMemory;

    JS_PUBLIC_API JSString* (*SM_NewExternalString)(
        JSContext* cx, const char16_t* chars, size_t length, const JSStringFinalizer* fin);

    JS_PUBLIC_API void (*SM_SetNativeStackQuota)(
        JSContext* cx, size_t systemCodeStackSize, size_t trustedScriptStackSize, size_t untrustedScriptStackSize) = &JS_SetNativeStackQuota;

    JS_PUBLIC_API bool (*SM_ValueToId)(JSContext* cx, JS::HandleValue v, JS::MutableHandleId idp) = &JS_ValueToId;

    JS_PUBLIC_API bool (*SM_IdToValue)(JSContext* cx, jsid id, JS::MutableHandle<JS::Value> vp) = &JS_IdToValue;

    JS_PUBLIC_API JSString* (*SM_ValueToSource)(JSContext* cx, JS::Handle<JS::Value> v) = &JS_ValueToSource;

    JS_PUBLIC_API JSObject* (*SM_InitClass)(
        JSContext* cx, JS::HandleObject obj, JS::HandleObject parent_proto,
        const JSClass* clasp, JSNative constructor, unsigned nargs,
        const JSPropertySpec* ps, const JSFunctionSpec* fs,
        const JSPropertySpec* static_ps, const JSFunctionSpec* static_fs) = &JS_InitClass;

    JS_PUBLIC_API const JSClass* (*SM_GetClass)(JSObject* obj) = &JS_GetClass;

    JS_PUBLIC_API bool (*SM_HasInstance)(
        JSContext* cx, JS::Handle<JSObject*> obj, JS::Handle<JS::Value> v, bool* bp) = &JS_HasInstance;

    JS_PUBLIC_API void* (*SM_GetPrivate)(JSObject* obj) = &JS_GetPrivate;

    JS_PUBLIC_API void (*SM_SetPrivate)(JSObject* obj, void* data) = &JS_SetPrivate;

    JS_PUBLIC_API JSObject* (*SM_GetConstructor)(JSContext* cx, JS::Handle<JSObject*> proto) = &JS_GetConstructor;

    JS_PUBLIC_API void* (*SM_GetInstancePrivate)(
        JSContext* cx, JS::Handle<JSObject*> obj, const JSClass* clasp, JS::CallArgs* args) = &JS_GetInstancePrivate;

    JS_PUBLIC_API JSObject* (*SM_NewGlobalObject)(
        JSContext* cx, const JSClass* clasp, JSPrincipals* principals,
        JS::OnNewGlobalHookOption hookOption, const JS::RealmOptions& options) = &JS_NewGlobalObject;

    JS_PUBLIC_API void (*SM_GlobalObjectTraceHook)(JSTracer* trc, JSObject* global) = &JS_GlobalObjectTraceHook;

    JS_PUBLIC_API JSObject* (*SM_NewObject)(JSContext* cx, const JSClass* clasp) = &JS_NewObject;

    JS_PUBLIC_API JSObject* (*SM_NewObjectWithGivenProto)(
        JSContext* cx, const JSClass* clasp, JS::Handle<JSObject*> proto) = &JS_NewObjectWithGivenProto;

    JS_PUBLIC_API bool (*SM_GetPrototype)(
        JSContext* cx, JS::HandleObject obj, JS::MutableHandleObject result) = &JS_GetPrototype;

    JS_PUBLIC_API bool (*SM_SetPrototype)(
        JSContext* cx, JS::HandleObject obj, JS::HandleObject proto) = &JS_SetPrototype;

    JS_PUBLIC_API bool (*SM_DefinePropertyById)(
        JSContext* cx, JS::HandleObject obj, JS::HandleId id, JS::HandleValue value,
        unsigned attrs) = &JS_DefinePropertyById;

    JS_PUBLIC_API bool (*SM_DefinePropertyByIdNative)(
        JSContext* cx, JS::HandleObject obj, JS::HandleId id,
        JSNative getter, JSNative setter, unsigned attrs) = &JS_DefinePropertyById;

    JS_PUBLIC_API bool (*SM_DefineProperty)(
        JSContext* cx, JS::HandleObject obj, const char* name, JS::HandleValue value,
        unsigned attrs) = &JS_DefineProperty;

    JS_PUBLIC_API bool (*SM_DefinePropertyNative)(
        JSContext* cx, JS::HandleObject obj, const char* name,
        JSNative getter, JSNative setter, unsigned attrs) = &JS_DefineProperty;

    JS_PUBLIC_API bool (*SM_DefineUCProperty)(
        JSContext* cx, JS::HandleObject obj, const char16_t* name, size_t namelen,
        JS::HandleValue value, unsigned attrs) = &JS_DefineUCProperty;

    JS_PUBLIC_API bool (*SM_DefineUCPropertyNative)(
        JSContext* cx, JS::HandleObject obj, const char16_t* name, size_t namelen,
        JS::HandleObject getter, JS::HandleObject setter, unsigned attrs) = &JS_DefineUCProperty;

    JS_PUBLIC_API bool (*SM_HasProperty)(
        JSContext* cx, JS::HandleObject obj, const char* name, bool* foundp) = &JS_HasProperty;

    JS_PUBLIC_API bool (*SM_HasUCProperty)(
        JSContext* cx, JS::HandleObject obj, const char16_t* name, size_t namelen, bool* vp) = &JS_HasUCProperty;

    JS_PUBLIC_API bool (*SM_GetPropertyById)(
        JSContext* cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) = &JS_GetPropertyById;

    JS_PUBLIC_API bool (*SM_GetProperty)(
        JSContext* cx, JS::HandleObject obj, const char* name, JS::MutableHandleValue vp) = &JS_GetProperty;

    JS_PUBLIC_API bool (*SM_GetUCProperty)(
        JSContext* cx, JS::HandleObject obj, const char16_t* name, size_t namelen, JS::MutableHandleValue vp) = &JS_GetUCProperty;

    JS_PUBLIC_API bool (*SM_GetElement)(
        JSContext* cx, JS::HandleObject obj, uint32_t index, JS::MutableHandleValue vp) = &JS_GetElement;

    JS_PUBLIC_API bool (*SM_SetProperty)(
        JSContext* cx, JS::HandleObject obj, const char* name, JS::HandleValue v) = &JS_SetProperty;

    JS_PUBLIC_API bool (*SM_SetUCProperty)(
        JSContext* cx, JS::HandleObject obj, const char16_t* name, size_t namelen, JS::HandleValue v) = &JS_SetUCProperty;

    JS_PUBLIC_API bool (*SM_SetElement)(
        JSContext* cx, JS::HandleObject obj, uint32_t index, JS::HandleValue v) = &JS_SetElement;

    JS_PUBLIC_API bool (*SM_DeletePropertyById)(
        JSContext* cx, JS::HandleObject obj, JS::HandleId id, JS::ObjectOpResult& result) = &JS_DeletePropertyById;

    JS_PUBLIC_API bool (*SM_DeleteElement)(
        JSContext* cx, JS::HandleObject obj, uint32_t index, JS::ObjectOpResult& result) = &JS_DeleteElement;

    JS_PUBLIC_API JS::RootedIdVector* SM_EnumerateToAutoIdVector(
        JSContext* cx, JS::HandleObject obj, size_t* length, jsid** data);

    JS_PUBLIC_API void SM_DestroyAutoIdVector(JS::RootedIdVector* v);

    JS_PUBLIC_API bool (*SM_CallFunctionValue)(
        JSContext* cx, JS::HandleObject obj, JS::HandleValue fval,
        const JS::HandleValueArray& args, JS::MutableHandleValue rval) = &JS_CallFunctionValue;

    JS_PUBLIC_API bool (*SM_CallFunction)(
        JSContext* cx, JS::HandleObject obj, JS::HandleFunction fun,
        const JS::HandleValueArray& args, JS::MutableHandleValue rval) = &JS_CallFunction;

    JS_PUBLIC_API bool (*SM_CallFunctionName)(
        JSContext* cx, JS::HandleObject obj, const char* name,
        const JS::HandleValueArray& args, JS::MutableHandleValue rval) = &JS_CallFunctionName;

    JS_PUBLIC_API JSObject* (*SM_New)(
        JSContext* cx, JS::HandleObject ctor, const JS::HandleValueArray& args) = &JS_New;

    JS_PUBLIC_API bool (*SM_DefineProperties)(
        JSContext* cx, JS::HandleObject obj, const JSPropertySpec* ps) = &JS_DefineProperties;

    JS_PUBLIC_API bool (*SM_AlreadyHasOwnUCProperty)(
        JSContext* cx, JS::HandleObject obj, const char16_t* name,
        size_t namelen, bool* foundp) = &JS_AlreadyHasOwnUCProperty;

    JS_PUBLIC_API JSObject* (*SM_NewArrayObject)(JSContext* cx, size_t length) = &JS_NewArrayObject;

    JS_PUBLIC_API JSObject* (*SM_NewArrayObject2)(
        JSContext* cx, const JS::HandleValueArray& contents) = &JS_NewArrayObject;

    JS_PUBLIC_API bool (*SM_IsArrayObject)(
        JSContext* cx, JS::HandleObject obj, bool* isArray) = &JS_IsArrayObject;

    JS_PUBLIC_API bool (*SM_GetArrayLength)(
        JSContext* cx, JS::Handle<JSObject*> obj, uint32_t* lengthp) = &JS_GetArrayLength;

    JS_PUBLIC_API uint64_t SM_GetReservedSlot(JSObject* obj, uint32_t index);

    JS_PUBLIC_API void (*SM_SetReservedSlot)(
        JSObject* obj, uint32_t index, const JS::Value& v) = &JS_SetReservedSlot;

    JS_PUBLIC_API JSFunction* (*SM_NewFunction)(
        JSContext* cx, JSNative call, unsigned nargs, unsigned flags, const char* name) = &JS_NewFunction;

    JS_PUBLIC_API JSString* (*SM_GetFunctionId)(JSFunction* fun) = &JS_GetFunctionId;

    JS_PUBLIC_API bool (*SM_ObjectIsFunction)(JSObject* obj) = &JS_ObjectIsFunction;

    JS_PUBLIC_API bool (*SM_DefineFunctions)(
        JSContext* cx, JS::Handle<JSObject*> obj, const JSFunctionSpec* fs) = &JS_DefineFunctions;

    JS_PUBLIC_API JSFunction* (*SM_DefineFunction)(
        JSContext* cx, JS::Handle<JSObject*> obj, const char* name, JSNative call,
        unsigned nargs, unsigned attrs) = &JS_DefineFunction;

    JS_PUBLIC_API JSFunction* (*SM_DefineUCFunction)(
        JSContext* cx, JS::Handle<JSObject*> obj,
        const char16_t* name, size_t namelen, JSNative call,
        unsigned nargs, unsigned attrs) = &JS_DefineUCFunction;

    JS_PUBLIC_API bool SM_CompileScript(
        JSContext* cx, const char* ascii, size_t length,
        const JS::ReadOnlyCompileOptions& options, JS::MutableHandleScript script);

    JS_PUBLIC_API bool SM_CompileUCScript(
        JSContext* cx, const char16_t* chars, size_t length,
        const JS::ReadOnlyCompileOptions& options, JS::MutableHandleScript script);
/*
    JS_PUBLIC_API JSString* (*SM_DecompileFunction)(
        JSContext* cx, JS::Handle<JSFunction*> fun) = &JS_DecompileFunction;
*/
    JS_PUBLIC_API bool (*SM_ExecuteScript)(
        JSContext* cx, JS::HandleScript script, JS::MutableHandleValue rval) = &JS_ExecuteScript;

    JS_PUBLIC_API bool (*SM_CheckForInterrupt)(JSContext* cx) = &JS_CheckForInterrupt;

    JS_PUBLIC_API bool (*SM_AddInterruptCallback)(
        JSContext* cx, JSInterruptCallback callback) = &JS_AddInterruptCallback;

    JS_PUBLIC_API bool (*SM_DisableInterruptCallback)(JSContext* cx) = &JS_DisableInterruptCallback;

    JS_PUBLIC_API void (*SM_ResetInterruptCallback)(JSContext* cx, bool enable) = &JS_ResetInterruptCallback;

    JS_PUBLIC_API void (*SM_RequestInterruptCallback)(JSContext* cx) = &JS_RequestInterruptCallback;

    JS_PUBLIC_API JSString* (*SM_NewStringCopyN)(
        JSContext* cx, const char* s, size_t n) = &JS_NewStringCopyN;

    JS_PUBLIC_API JSString* (*SM_NewStringCopyUTF8Z)(
        JSContext* cx, const JS::ConstUTF8CharsZ s) = &JS_NewStringCopyUTF8Z;

    JS_PUBLIC_API JS::Value (*SM_GetEmptyStringValue)(JSContext* cx) = &JS_GetEmptyStringValue;

    JS_PUBLIC_API JSString* (*SM_NewUCStringCopyN)(
        JSContext* cx, const char16_t* s, size_t n) = &JS_NewUCStringCopyN;

    JS_PUBLIC_API size_t (*SM_GetStringLength)(JSString* str) = &JS_GetStringLength;

    JS_PUBLIC_API bool (*SM_StringHasLatin1Chars)(JSString* str) = &JS_StringHasLatin1Chars;

    JS_PUBLIC_API const JS::Latin1Char* (*SM_GetLatin1StringCharsAndLength)(
        JSContext* cx, const JS::AutoRequireNoGC& nogc, JSString* str, size_t* length) = &JS_GetLatin1StringCharsAndLength;

    JS_PUBLIC_API const char16_t* (*SM_GetTwoByteStringCharsAndLength)(
        JSContext* cx, const JS::AutoRequireNoGC& nogc, JSString* str, size_t* length) = &JS_GetTwoByteStringCharsAndLength;

    JS_PUBLIC_API bool (*SM_Stringify)(
        JSContext* cx, JS::MutableHandleValue value, JS::HandleObject replacer,
        JS::HandleValue space, JSONWriteCallback callback, void* data) = &JS_Stringify;

    JS_PUBLIC_API bool (*SM_ParseJSON)(
        JSContext* cx, const char16_t* chars, uint32_t len, JS::MutableHandleValue vp) = &JS_ParseJSON;

    JS_PUBLIC_API void (*SM_ReportErrorASCII)(
        JSContext* cx, const char* format, ...) = &JS_ReportErrorASCII;

    JS_PUBLIC_API void (*SM_ReportErrorNumberUC)(
        JSContext* cx, JSErrorCallback errorCallback, void* userRef, const unsigned errorNumber, ...) = &JS_ReportErrorNumberUC;

    JS_PUBLIC_API void (*SM_ReportErrorNumberUTF8)(
        JSContext* cx, JSErrorCallback errorCallback, void* userRef, const unsigned errorNumber, ...) = &JS_ReportErrorNumberUTF8;

    JS_PUBLIC_API void (*SM_ReportOutOfMemory)(JSContext* cx) = &JS_ReportOutOfMemory;

    JS_PUBLIC_API JS::WarningReporter (*SM_GetWarningReporter)(JSContext* cx) = &JS::GetWarningReporter;

    JS_PUBLIC_API JS::WarningReporter (*SM_SetWarningReporter)(JSContext* cx, JS::WarningReporter reporter) = &JS::SetWarningReporter;

    JS_PUBLIC_API JSObject* (*SM_NewDateObject)(
        JSContext* cx, int year, int mon, int mday, int hour, int min, int sec) = &JS::NewDateObject;

    JS_PUBLIC_API JSObject* SM_NewDateObjectMsec(JSContext* cx, double msec);

    JS_PUBLIC_API bool (*SM_ObjectIsDate)(JSContext* cx, JS::HandleObject obj, bool* isDate) = &JS::ObjectIsDate;

    JS_PUBLIC_API bool (*SM_IsExceptionPending)(JSContext* cx) = &JS_IsExceptionPending;

    JS_PUBLIC_API bool (*SM_GetPendingException)(JSContext* cx, JS::MutableHandleValue vp) = &JS_GetPendingException;

    JS_PUBLIC_API void (*SM_SetPendingException)(
        JSContext* cx, JS::HandleValue v, JS::ExceptionStackBehavior behavior) = &JS_SetPendingException;

    JS_PUBLIC_API void (*SM_ClearPendingException)(JSContext* cx) = &JS_ClearPendingException;

    JS_PUBLIC_API JSErrorReport* (*SM_ErrorFromException)(JSContext* cx, JS::HandleObject obj) = &JS_ErrorFromException;

    JS_PUBLIC_API void* SM_GetContextOptions(JSContext* cx);

    JS_PUBLIC_API void* SM_NewRootedValue(JSContext* cx, uint64_t initial);

    JS_PUBLIC_API void SM_FreeRootedValue(void* val);

    JS_PUBLIC_API void* SM_NewRootedObject(JSContext* cx, JSObject* initial);

    JS_PUBLIC_API void SM_FreeRootedObject(void* obj);

    JS_PUBLIC_API void* SM_NewRootedString(JSContext* cx, JSString* initial);

    JS_PUBLIC_API void SM_FreeRootedString(void* str);

    JS_PUBLIC_API void* SM_NewCompileOptions(JSContext* cx);

    JS_PUBLIC_API void SM_SetCompileOptionsFileAndLine(
        JS::CompileOptions& options, const char* f, unsigned l);

    JS_PUBLIC_API void SM_FreeCompileOptions(void* co);

    JS_PUBLIC_API bool SM_EvaluateScript(
        JSContext* cx, const JS::ReadOnlyCompileOptions& options,
        const char* bytes, size_t length, JS::MutableHandleValue rval);

    JS_PUBLIC_API bool SM_EvaluateUTF8Script(
        JSContext* cx, const JS::ReadOnlyCompileOptions& options,
        const mozilla::Utf8Unit* utf8chars, size_t length, JS::MutableHandleValue rval);

    JS_PUBLIC_API bool SM_EvaluateUCScript(
        JSContext* cx, const JS::ReadOnlyCompileOptions& options,
        const char16_t* chars, size_t length, JS::MutableHandleValue rval);

    JS_PUBLIC_API bool (*SM_ComputeThis)(JSContext* cx, JS::Value* vp, JS::MutableHandleObject thisObject) = &JS::detail::ComputeThis;

    // Array functions from jsfriendsapi.h

    JS_FRIEND_API JSObject* (*SM_NewInt8Array)(JSContext* cx, uint32_t nelements) = &JS_NewInt8Array;

    JS_FRIEND_API JSObject* (*SM_NewUint8Array)(JSContext* cx, uint32_t nelements) = &JS_NewUint8Array;

    JS_FRIEND_API JSObject* (*SM_NewUint8ClampedArray)(JSContext* cx, uint32_t nelements) = &JS_NewUint8ClampedArray;

    JS_FRIEND_API JSObject* (*SM_NewInt16Array)(JSContext* cx, uint32_t nelements) = &JS_NewInt16Array;

    JS_FRIEND_API JSObject* (*SM_NewUint16Array)(JSContext* cx, uint32_t nelements) = &JS_NewUint16Array;

    JS_FRIEND_API JSObject* (*SM_NewInt32Array)(JSContext* cx, uint32_t nelements) = &JS_NewInt32Array;

    JS_FRIEND_API JSObject* (*SM_NewUint32Array)(JSContext* cx, uint32_t nelements) = &JS_NewUint32Array;

    JS_FRIEND_API JSObject* (*SM_NewFloat32Array)(JSContext* cx, uint32_t nelements) = &JS_NewFloat32Array;

    JS_FRIEND_API JSObject* (*SM_NewFloat64Array)(JSContext* cx, uint32_t nelements) = &JS_NewFloat64Array;

    JS_FRIEND_API JSObject* (*SM_NewInt8ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewInt8ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewUint8ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewUint8ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewUint8ClampedArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewUint8ClampedArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewInt16ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewInt16ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewUint16ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewUint16ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewInt32ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewInt32ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewUint32ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewUint32ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewFloat32ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewFloat32ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewFloat64ArrayFromArray)(JSContext* cx, JS::HandleObject array) = &JS_NewFloat64ArrayFromArray;

    JS_FRIEND_API JSObject* (*SM_NewInt8ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewInt8ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewUint8ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewUint8ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewUint8ClampedArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewUint8ClampedArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewInt16ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewInt16ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewUint16ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewUint16ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewInt32ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewInt32ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewUint32ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewUint32ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewFloat32ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewFloat32ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewFloat64ArrayWithBuffer)(
        JSContext* cx, JS::HandleObject arrayBuffer, uint32_t byteOffset, int32_t length) = &JS_NewFloat64ArrayWithBuffer;

    JS_FRIEND_API JSObject* (*SM_NewSharedArrayBuffer)(JSContext* cx, uint32_t nbytes) = &JS::NewSharedArrayBuffer;

    JS_FRIEND_API JSObject* (*SM_NewArrayBuffer)(JSContext* cx, uint32_t nbytes) = &JS::NewArrayBuffer;

    JS_FRIEND_API bool (*SM_IsTypedArrayObject)(JSObject* obj) = &JS_IsTypedArrayObject;

    JS_FRIEND_API bool (*SM_IsArrayBufferViewObject)(JSObject* obj) = &JS_IsArrayBufferViewObject;

    JS_FRIEND_API bool (*SM_IsInt8Array)(JSObject* obj) = &JS_IsInt8Array;

    JS_FRIEND_API bool (*SM_IsUint8Array)(JSObject* obj) = &JS_IsUint8Array;

    JS_FRIEND_API bool (*SM_IsUint8ClampedArray)(JSObject* obj) = &JS_IsUint8ClampedArray;

    JS_FRIEND_API bool (*SM_IsInt16Array)(JSObject* obj) = &JS_IsInt16Array;

    JS_FRIEND_API bool (*SM_IsUint16Array)(JSObject* obj) = &JS_IsUint16Array;

    JS_FRIEND_API bool (*SM_IsInt32Array)(JSObject* obj) = &JS_IsInt32Array;

    JS_FRIEND_API bool (*SM_IsUint32Array)(JSObject* obj) = &JS_IsUint32Array;

    JS_FRIEND_API bool (*SM_IsFloat32Array)(JSObject* obj) = &JS_IsFloat32Array;

    JS_FRIEND_API bool (*SM_IsFloat64Array)(JSObject* obj) = &JS_IsFloat64Array;

    JS_FRIEND_API bool (*SM_GetTypedArraySharedness)(JSObject* obj) = &JS_GetTypedArraySharedness;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsInt8Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, int8_t** data) = &JS_GetObjectAsInt8Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsUint8Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, uint8_t** data) = &JS_GetObjectAsUint8Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsUint8ClampedArray)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, uint8_t** data) = &JS_GetObjectAsUint8ClampedArray;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsInt16Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, int16_t** data) = &JS_GetObjectAsInt16Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsUint16Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, uint16_t** data) = &JS_GetObjectAsUint16Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsInt32Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, int32_t** data) = &JS_GetObjectAsInt32Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsUint32Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, uint32_t** data) = &JS_GetObjectAsUint32Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsFloat32Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, float** data) = &JS_GetObjectAsFloat32Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsFloat64Array)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, double** data) = &JS_GetObjectAsFloat64Array;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsArrayBufferView)(
        JSObject* obj, uint32_t* length, bool* isSharedMemory, uint8_t** data) = &JS_GetObjectAsArrayBufferView;

    JS_FRIEND_API JSObject* (*SM_GetObjectAsArrayBuffer)(
        JSObject* obj, uint32_t* length, uint8_t** data) = &JS::GetObjectAsArrayBuffer;

    JS_FRIEND_API js::Scalar::Type (*SM_GetArrayBufferViewType)(JSObject* obj) = &JS_GetArrayBufferViewType;

    JS_FRIEND_API bool (*SM_IsArrayBufferObject)(JSObject* obj) = &JS::IsArrayBufferObject;

    JS_FRIEND_API bool (*SM_IsSharedArrayBufferObject)(JSObject* obj) = &JS::IsSharedArrayBufferObject;

    JS_FRIEND_API uint32_t (*SM_GetArrayBufferByteLength)(JSObject* obj) = &JS::GetArrayBufferByteLength;

    JS_FRIEND_API uint32_t (*SM_GetSharedArrayBufferByteLength)(JSObject* obj) = &JS::GetSharedArrayBufferByteLength;

    JS_FRIEND_API bool (*SM_ArrayBufferHasData)(JSObject* obj) = &JS::ArrayBufferHasData;

    JS_FRIEND_API uint8_t* (*SM_GetArrayBufferData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS::GetArrayBufferData;

    JS_FRIEND_API bool (*SM_IsMappedArrayBufferObject)(JSObject* obj) = &JS::IsMappedArrayBufferObject;

    JS_FRIEND_API uint32_t (*SM_GetTypedArrayLength)(JSObject* obj) = &JS_GetTypedArrayLength;

    JS_FRIEND_API uint32_t (*SM_GetTypedArrayByteOffset)(JSObject* obj) = &JS_GetTypedArrayByteOffset;

    JS_FRIEND_API uint32_t (*SM_GetTypedArrayByteLength)(JSObject* obj) = &JS_GetTypedArrayByteLength;

    JS_FRIEND_API uint32_t (*SM_GetArrayBufferViewByteLength)(JSObject* obj) = &JS_GetArrayBufferViewByteLength;

    JS_FRIEND_API int8_t* (*SM_GetInt8ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetInt8ArrayData;

    JS_FRIEND_API uint8_t* (*SM_GetUint8ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetUint8ArrayData;

    JS_FRIEND_API uint8_t* (*SM_GetUint8ClampedArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetUint8ClampedArrayData;

    JS_FRIEND_API int16_t* (*SM_GetInt16ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetInt16ArrayData;

    JS_FRIEND_API uint16_t* (*SM_GetUint16ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetUint16ArrayData;

    JS_FRIEND_API int32_t* (*SM_GetInt32ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetInt32ArrayData;

    JS_FRIEND_API uint32_t* (*SM_GetUint32ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetUint32ArrayData;

    JS_FRIEND_API float* (*SM_GetFloat32ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetFloat32ArrayData;

    JS_FRIEND_API double* (*SM_GetFloat64ArrayData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetFloat64ArrayData;

    JS_FRIEND_API void* (*SM_GetArrayBufferViewData)(
        JSObject* obj, bool* isSharedMemory, const JS::AutoRequireNoGC&) = &JS_GetArrayBufferViewData;

    JS_FRIEND_API JSObject* (*SM_GetArrayBufferViewBuffer)(
        JSContext* cx, JS::HandleObject obj, bool* isSharedMemory) = &JS_GetArrayBufferViewBuffer;

    JS_PUBLIC_API bool SM_InitModuleClasses(JSContext* cx, JS::Handle<JSObject*> obj);

    JS_PUBLIC_API JSObject* SM_CompileModule(
        JSContext* cx, JS::Handle<JSObject*> obj, JS::ReadOnlyCompileOptions& options,
        const char16_t* chars, size_t length);

    JS_PUBLIC_API void SM_SetModuleResolveHook(
        JSContext* cx, JS::ModuleResolveHook hook);

    JS_PUBLIC_API void* SM_NewRealmOptions();

    JS_PUBLIC_API void SM_FreeRealmOptions(void* opt);
}
#endif
