#include "synsm.h"

#include <mozilla/Assertions.h>
#include <js/SourceText.h>
#include <js/CharacterEncoding.h>

// Declared in vm/Runtime.h
namespace js {
    extern bool gCanUseExtraThreads;
}

JS_PUBLIC_API void SM_DisableExtraThreads(void)
{
    js::gCanUseExtraThreads = false;
}

JS_PUBLIC_API JS::RootedIdVector* SM_EnumerateToAutoIdVector(
    JSContext* cx, JS::HandleObject obj, size_t* length, jsid** data)
{
    // TODO:
    // js::AssertHeapIsIdle(cx);
    // CHECK_REQUEST(cx);
    // assertSameCompartment(cx, obj);

    JS::RootedIdVector* v = new JS::RootedIdVector(cx);
    if (!GetPropertyKeys(cx, obj, JSITER_OWNONLY, v)) {
        delete v;
        *length = 0;
        *data = nullptr;
        return nullptr;
    }

    *length = v->length();
    *data = v->begin();
    return v;
}

JS_PUBLIC_API void SM_DestroyAutoIdVector(JS::RootedIdVector* v)
{
    delete v;
}

JS_PUBLIC_API uint64_t SM_GetReservedSlot(JSObject* obj, uint32_t index)
{
    return js::GetReservedSlot(obj, index).asRawBits();
}

JS_PUBLIC_API bool SM_CompileScript(
    JSContext* cx, const char* ascii, size_t length,
    const JS::ReadOnlyCompileOptions& options, JS::MutableHandleScript script)
{
    JS::UTF8CharsZ chars = JS::CharsToNewUTF8CharsZ(cx, JS::Latin1Chars(ascii, length));
    JS::SourceText<mozilla::Utf8Unit> srcBuf;
    if (!srcBuf.init(cx, chars.c_str(), strlen(chars.c_str()), JS::SourceOwnership::Borrowed))
        return false;
    script.set(JS::CompileDontInflate(cx, options, srcBuf));
    return true;
}

JS_PUBLIC_API bool SM_CompileUCScript(
    JSContext* cx, const char16_t* chars, size_t length,
    const JS::ReadOnlyCompileOptions& options, JS::MutableHandleScript script)
{
    JS::SourceText<char16_t> srcBuf;
    if (!srcBuf.init(cx, chars, length, JS::SourceOwnership::Borrowed))
        return false;
    script.set(JS::Compile(cx, options, srcBuf));
    return true;
}

JS_PUBLIC_API JSObject* SM_NewDateObjectMsec(JSContext* cx, double msec)
{
    JS::ClippedTime time = JS::TimeClip(msec);
    return JS::NewDateObject(cx, time);
}

JS_PUBLIC_API void* SM_GetContextOptions(JSContext* cx)
{
    return &JS::ContextOptionsRef(cx);
}

JS_PUBLIC_API void* SM_NewRootedValue(JSContext* cx, uint64_t initial)
{
    return js_new<JS::RootedValue>(cx, JS::Value::fromRawBits(initial));
}

JS_PUBLIC_API void SM_FreeRootedValue(void* val)
{
    js_delete(reinterpret_cast<JS::RootedValue*>(val));
}

JS_PUBLIC_API void* SM_NewRootedObject(JSContext* cx, JSObject* initial)
{
    return js_new<JS::RootedObject>(cx, initial);
}

JS_PUBLIC_API void SM_FreeRootedObject(void* obj)
{
    js_delete(reinterpret_cast<JS::RootedObject*>(obj));
}

JS_PUBLIC_API void* SM_NewRootedString(JSContext* cx, JSString* initial)
{
    return js_new<JS::RootedString>(cx, initial);
}

JS_PUBLIC_API void SM_FreeRootedString(void* str)
{
    js_delete(reinterpret_cast<JS::RootedString*>(str));
}

JS_PUBLIC_API void* SM_NewCompileOptions(JSContext* cx)
{
    return js_new<JS::CompileOptions>(cx);
}

JS_PUBLIC_API void SM_SetCompileOptionsFileAndLine(JS::CompileOptions& options, const char* f, unsigned l)
{
    options.setFileAndLine(f, l);
}

JS_PUBLIC_API void SM_FreeCompileOptions(void* co)
{
    js_delete(reinterpret_cast<JS::CompileOptions*>(co));
}

JS_PUBLIC_API bool SM_EvaluateScript(
    JSContext* cx, const JS::ReadOnlyCompileOptions& options,
    const char* bytes, size_t length, JS::MutableHandleValue rval)
{
    JS::UTF8CharsZ chars = JS::CharsToNewUTF8CharsZ(cx, JS::Latin1Chars(bytes, length));
    JS::SourceText<mozilla::Utf8Unit> srcBuf;
    if (!srcBuf.init(cx, chars.c_str(), strlen(chars.c_str()), JS::SourceOwnership::Borrowed))
        return false;
    return JS::EvaluateDontInflate(cx, options, srcBuf, rval);
}

JS_PUBLIC_API bool SM_EvaluateUTF8Script(
    JSContext* cx, const JS::ReadOnlyCompileOptions& options,
    const mozilla::Utf8Unit* utf8chars, size_t length, JS::MutableHandleValue rval)
{
    JS::SourceText<mozilla::Utf8Unit> srcBuf;
    if (!srcBuf.init(cx, utf8chars, length, JS::SourceOwnership::Borrowed))
        return false;
    return JS::EvaluateDontInflate(cx, options, srcBuf, rval);
}

JS_PUBLIC_API bool SM_EvaluateUCScript(
    JSContext* cx, const JS::ReadOnlyCompileOptions& options,
    const char16_t* chars, size_t length, JS::MutableHandleValue rval)
{
    JS::SourceText<char16_t> srcBuf;
    if (!srcBuf.init(cx, chars, length, JS::SourceOwnership::Borrowed))
        return false;
    return JS::Evaluate(cx, options, srcBuf, rval);
}

JS_PUBLIC_API bool SM_InitModuleClasses(JSContext* cx, JS::HandleObject obj)
{
    // Intentionally commented out
    //return js::InitModuleClasses(cx, obj);
    return true;
}

JS_PUBLIC_API JSObject* SM_CompileModule(JSContext* cx, JS::HandleObject obj, JS::ReadOnlyCompileOptions& options,
    const char16_t* chars, size_t length)
{
    JS::SourceText<char16_t> srcBuf;
    JS::Rooted<JSObject*> module(cx);
    return (srcBuf.init(cx, chars, length, JS::SourceOwnership::Borrowed) && JS::CompileModule(cx, options, srcBuf, &module)) ? module.get() : nullptr;
}

JS_PUBLIC_API void SM_SetModuleResolveHook(
    JSContext* cx, JS::ModuleResolveHook hook)
{
    JS::SetModuleResolveHook(JS_GetRuntime(cx), hook);
}

JS_PUBLIC_API void* SM_NewRealmOptions()
{
    return js_new<JS::RealmOptions>();
}

JS_PUBLIC_API void SM_FreeRealmOptions(void* opt)
{
    js_delete(reinterpret_cast<JS::RealmOptions*>(opt));
}
