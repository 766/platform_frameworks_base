/* //device/libs/android_runtime/com_google_android_gles_jni_GLImpl.cpp
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

// This source file is automatically generated

#include <android_runtime/AndroidRuntime.h>
#include <utils/misc.h>

#include <assert.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

/* special calls implemented in Android's GLES wrapper used to more
 * efficiently bound-check passed arrays */
extern "C" {
GL_API void GL_APIENTRY glColorPointerBounds(GLint size, GLenum type, GLsizei stride,
        const GLvoid *ptr, GLsizei count);
GL_API void GL_APIENTRY glNormalPointerBounds(GLenum type, GLsizei stride,
        const GLvoid *pointer, GLsizei count);
GL_API void GL_APIENTRY glTexCoordPointerBounds(GLint size, GLenum type,
        GLsizei stride, const GLvoid *pointer, GLsizei count);
GL_API void GL_APIENTRY glVertexPointerBounds(GLint size, GLenum type,
        GLsizei stride, const GLvoid *pointer, GLsizei count);
}

static int initialized = 0;

static jclass nioAccessClass;
static jclass bufferClass;
static jclass OOMEClass;
static jclass UOEClass;
static jclass IAEClass;
static jclass AIOOBEClass;
static jmethodID getBasePointerID;
static jmethodID getBaseArrayID;
static jmethodID getBaseArrayOffsetID;
static jfieldID positionID;
static jfieldID limitID;
static jfieldID elementSizeShiftID;

/* Cache method IDs each time the class is loaded. */

static void
nativeClassInitBuffer(JNIEnv *_env)
{
    jclass nioAccessClassLocal = _env->FindClass("java/nio/NIOAccess");
    nioAccessClass = (jclass) _env->NewGlobalRef(nioAccessClassLocal);

    jclass bufferClassLocal = _env->FindClass("java/nio/Buffer");
    bufferClass = (jclass) _env->NewGlobalRef(bufferClassLocal);

    getBasePointerID = _env->GetStaticMethodID(nioAccessClass,
            "getBasePointer", "(Ljava/nio/Buffer;)J");
    getBaseArrayID = _env->GetStaticMethodID(nioAccessClass,
            "getBaseArray", "(Ljava/nio/Buffer;)Ljava/lang/Object;");
    getBaseArrayOffsetID = _env->GetStaticMethodID(nioAccessClass,
            "getBaseArrayOffset", "(Ljava/nio/Buffer;)I");

    positionID = _env->GetFieldID(bufferClass, "position", "I");
    limitID = _env->GetFieldID(bufferClass, "limit", "I");
    elementSizeShiftID =
        _env->GetFieldID(bufferClass, "_elementSizeShift", "I");
}

static void
nativeClassInit(JNIEnv *_env, jclass glImplClass)
{
    nativeClassInitBuffer(_env);

    jclass IAEClassLocal =
        _env->FindClass("java/lang/IllegalArgumentException");
    jclass OOMEClassLocal =
         _env->FindClass("java/lang/OutOfMemoryError");
    jclass UOEClassLocal =
         _env->FindClass("java/lang/UnsupportedOperationException");
    jclass AIOOBEClassLocal =
         _env->FindClass("java/lang/ArrayIndexOutOfBoundsException");

    IAEClass = (jclass) _env->NewGlobalRef(IAEClassLocal);
    OOMEClass = (jclass) _env->NewGlobalRef(OOMEClassLocal);
    UOEClass = (jclass) _env->NewGlobalRef(UOEClassLocal);
    AIOOBEClass = (jclass) _env->NewGlobalRef(AIOOBEClassLocal);
}

static void *
getPointer(JNIEnv *_env, jobject buffer, jarray *array, jint *remaining)
{
    jint position;
    jint limit;
    jint elementSizeShift;
    jlong pointer;
    jint offset;
    void *data;

    position = _env->GetIntField(buffer, positionID);
    limit = _env->GetIntField(buffer, limitID);
    elementSizeShift = _env->GetIntField(buffer, elementSizeShiftID);
    *remaining = (limit - position) << elementSizeShift;
    pointer = _env->CallStaticLongMethod(nioAccessClass,
            getBasePointerID, buffer);
    if (pointer != 0L) {
        *array = NULL;
        return (void *) (jint) pointer;
    }
    
    *array = (jarray) _env->CallStaticObjectMethod(nioAccessClass,
            getBaseArrayID, buffer);
    offset = _env->CallStaticIntMethod(nioAccessClass,
            getBaseArrayOffsetID, buffer);
    data = _env->GetPrimitiveArrayCritical(*array, (jboolean *) 0);
    
    return (void *) ((char *) data + offset);
}

static void
releasePointer(JNIEnv *_env, jarray array, void *data, jboolean commit)
{
    _env->ReleasePrimitiveArrayCritical(array, data,
					   commit ? 0 : JNI_ABORT);
}

static void *
getDirectBufferPointer(JNIEnv *_env, jobject buffer) {
    char* buf = (char*) _env->GetDirectBufferAddress(buffer);
    if (buf) {
        jint position = _env->GetIntField(buffer, positionID);
        jint elementSizeShift = _env->GetIntField(buffer, elementSizeShiftID);
        buf += position << elementSizeShift;
    } else {
        _env->ThrowNew(IAEClass, "Must use a native order direct Buffer");
    }
    return (void*) buf;
}

static int
getNumCompressedTextureFormats() {
    int numCompressedTextureFormats = 0;
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numCompressedTextureFormats);
    return numCompressedTextureFormats;
}

// --------------------------------------------------------------------------

/* void glActiveTexture ( GLenum texture ) */
static void
android_glActiveTexture__I
  (JNIEnv *_env, jobject _this, jint texture) {
    glActiveTexture(
        (GLenum)texture
    );
}

/* void glAlphaFunc ( GLenum func, GLclampf ref ) */
static void
android_glAlphaFunc__IF
  (JNIEnv *_env, jobject _this, jint func, jfloat ref) {
    glAlphaFunc(
        (GLenum)func,
        (GLclampf)ref
    );
}

/* void glAlphaFuncx ( GLenum func, GLclampx ref ) */
static void
android_glAlphaFuncx__II
  (JNIEnv *_env, jobject _this, jint func, jint ref) {
    glAlphaFuncx(
        (GLenum)func,
        (GLclampx)ref
    );
}

/* void glBindTexture ( GLenum target, GLuint texture ) */
static void
android_glBindTexture__II
  (JNIEnv *_env, jobject _this, jint target, jint texture) {
    glBindTexture(
        (GLenum)target,
        (GLuint)texture
    );
}

/* void glBlendFunc ( GLenum sfactor, GLenum dfactor ) */
static void
android_glBlendFunc__II
  (JNIEnv *_env, jobject _this, jint sfactor, jint dfactor) {
    glBlendFunc(
        (GLenum)sfactor,
        (GLenum)dfactor
    );
}

/* void glClear ( GLbitfield mask ) */
static void
android_glClear__I
  (JNIEnv *_env, jobject _this, jint mask) {
    glClear(
        (GLbitfield)mask
    );
}

/* void glClearColor ( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ) */
static void
android_glClearColor__FFFF
  (JNIEnv *_env, jobject _this, jfloat red, jfloat green, jfloat blue, jfloat alpha) {
    glClearColor(
        (GLclampf)red,
        (GLclampf)green,
        (GLclampf)blue,
        (GLclampf)alpha
    );
}

/* void glClearColorx ( GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha ) */
static void
android_glClearColorx__IIII
  (JNIEnv *_env, jobject _this, jint red, jint green, jint blue, jint alpha) {
    glClearColorx(
        (GLclampx)red,
        (GLclampx)green,
        (GLclampx)blue,
        (GLclampx)alpha
    );
}

/* void glClearDepthf ( GLclampf depth ) */
static void
android_glClearDepthf__F
  (JNIEnv *_env, jobject _this, jfloat depth) {
    glClearDepthf(
        (GLclampf)depth
    );
}

/* void glClearDepthx ( GLclampx depth ) */
static void
android_glClearDepthx__I
  (JNIEnv *_env, jobject _this, jint depth) {
    glClearDepthx(
        (GLclampx)depth
    );
}

/* void glClearStencil ( GLint s ) */
static void
android_glClearStencil__I
  (JNIEnv *_env, jobject _this, jint s) {
    glClearStencil(
        (GLint)s
    );
}

/* void glClientActiveTexture ( GLenum texture ) */
static void
android_glClientActiveTexture__I
  (JNIEnv *_env, jobject _this, jint texture) {
    glClientActiveTexture(
        (GLenum)texture
    );
}

/* void glColor4f ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) */
static void
android_glColor4f__FFFF
  (JNIEnv *_env, jobject _this, jfloat red, jfloat green, jfloat blue, jfloat alpha) {
    glColor4f(
        (GLfloat)red,
        (GLfloat)green,
        (GLfloat)blue,
        (GLfloat)alpha
    );
}

/* void glColor4x ( GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha ) */
static void
android_glColor4x__IIII
  (JNIEnv *_env, jobject _this, jint red, jint green, jint blue, jint alpha) {
    glColor4x(
        (GLfixed)red,
        (GLfixed)green,
        (GLfixed)blue,
        (GLfixed)alpha
    );
}

/* void glColorMask ( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha ) */
static void
android_glColorMask__ZZZZ
  (JNIEnv *_env, jobject _this, jboolean red, jboolean green, jboolean blue, jboolean alpha) {
    glColorMask(
        (GLboolean)red,
        (GLboolean)green,
        (GLboolean)blue,
        (GLboolean)alpha
    );
}

/* void glColorPointer ( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer ) */
static void
android_glColorPointerBounds__IIILjava_nio_Buffer_2I
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jobject pointer_buf, jint remaining) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pointer = (GLvoid *) 0;

    if (pointer_buf) {
        pointer = (GLvoid *) getDirectBufferPointer(_env, pointer_buf);
        if ( ! pointer ) {
            return;
        }
    }
    glColorPointerBounds(
        (GLint)size,
        (GLenum)type,
        (GLsizei)stride,
        (GLvoid *)pointer,
        (GLsizei)remaining
    );
}

/* void glCompressedTexImage2D ( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data ) */
static void
android_glCompressedTexImage2D__IIIIIIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint target, jint level, jint internalformat, jint width, jint height, jint border, jint imageSize, jobject data_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *data = (GLvoid *) 0;

    data = (GLvoid *)getPointer(_env, data_buf, &_array, &_remaining);
    glCompressedTexImage2D(
        (GLenum)target,
        (GLint)level,
        (GLenum)internalformat,
        (GLsizei)width,
        (GLsizei)height,
        (GLint)border,
        (GLsizei)imageSize,
        (GLvoid *)data
    );
    if (_array) {
        releasePointer(_env, _array, data, JNI_FALSE);
    }
}

/* void glCompressedTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data ) */
static void
android_glCompressedTexSubImage2D__IIIIIIIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint target, jint level, jint xoffset, jint yoffset, jint width, jint height, jint format, jint imageSize, jobject data_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *data = (GLvoid *) 0;

    data = (GLvoid *)getPointer(_env, data_buf, &_array, &_remaining);
    glCompressedTexSubImage2D(
        (GLenum)target,
        (GLint)level,
        (GLint)xoffset,
        (GLint)yoffset,
        (GLsizei)width,
        (GLsizei)height,
        (GLenum)format,
        (GLsizei)imageSize,
        (GLvoid *)data
    );
    if (_array) {
        releasePointer(_env, _array, data, JNI_FALSE);
    }
}

/* void glCopyTexImage2D ( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border ) */
static void
android_glCopyTexImage2D__IIIIIIII
  (JNIEnv *_env, jobject _this, jint target, jint level, jint internalformat, jint x, jint y, jint width, jint height, jint border) {
    glCopyTexImage2D(
        (GLenum)target,
        (GLint)level,
        (GLenum)internalformat,
        (GLint)x,
        (GLint)y,
        (GLsizei)width,
        (GLsizei)height,
        (GLint)border
    );
}

/* void glCopyTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height ) */
static void
android_glCopyTexSubImage2D__IIIIIIII
  (JNIEnv *_env, jobject _this, jint target, jint level, jint xoffset, jint yoffset, jint x, jint y, jint width, jint height) {
    glCopyTexSubImage2D(
        (GLenum)target,
        (GLint)level,
        (GLint)xoffset,
        (GLint)yoffset,
        (GLint)x,
        (GLint)y,
        (GLsizei)width,
        (GLsizei)height
    );
}

/* void glCullFace ( GLenum mode ) */
static void
android_glCullFace__I
  (JNIEnv *_env, jobject _this, jint mode) {
    glCullFace(
        (GLenum)mode
    );
}

/* void glDeleteTextures ( GLsizei n, const GLuint *textures ) */
static void
android_glDeleteTextures__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray textures_ref, jint offset) {
    GLuint *textures_base = (GLuint *) 0;
    jint _remaining;
    GLuint *textures = (GLuint *) 0;

    if (!textures_ref) {
        _env->ThrowNew(IAEClass, "textures == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(textures_ref) - offset;
    if (_remaining < n) {
        _env->ThrowNew(IAEClass, "length - offset < n");
        goto exit;
    }
    textures_base = (GLuint *)
        _env->GetPrimitiveArrayCritical(textures_ref, (jboolean *)0);
    textures = textures_base + offset;

    glDeleteTextures(
        (GLsizei)n,
        (GLuint *)textures
    );

exit:
    if (textures_base) {
        _env->ReleasePrimitiveArrayCritical(textures_ref, textures_base,
            JNI_ABORT);
    }
}

/* void glDeleteTextures ( GLsizei n, const GLuint *textures ) */
static void
android_glDeleteTextures__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject textures_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLuint *textures = (GLuint *) 0;

    textures = (GLuint *)getPointer(_env, textures_buf, &_array, &_remaining);
    if (_remaining < n) {
        _env->ThrowNew(IAEClass, "remaining() < n");
        goto exit;
    }
    glDeleteTextures(
        (GLsizei)n,
        (GLuint *)textures
    );

exit:
    if (_array) {
        releasePointer(_env, _array, textures, JNI_FALSE);
    }
}

/* void glDepthFunc ( GLenum func ) */
static void
android_glDepthFunc__I
  (JNIEnv *_env, jobject _this, jint func) {
    glDepthFunc(
        (GLenum)func
    );
}

/* void glDepthMask ( GLboolean flag ) */
static void
android_glDepthMask__Z
  (JNIEnv *_env, jobject _this, jboolean flag) {
    glDepthMask(
        (GLboolean)flag
    );
}

/* void glDepthRangef ( GLclampf zNear, GLclampf zFar ) */
static void
android_glDepthRangef__FF
  (JNIEnv *_env, jobject _this, jfloat zNear, jfloat zFar) {
    glDepthRangef(
        (GLclampf)zNear,
        (GLclampf)zFar
    );
}

/* void glDepthRangex ( GLclampx zNear, GLclampx zFar ) */
static void
android_glDepthRangex__II
  (JNIEnv *_env, jobject _this, jint zNear, jint zFar) {
    glDepthRangex(
        (GLclampx)zNear,
        (GLclampx)zFar
    );
}

/* void glDisable ( GLenum cap ) */
static void
android_glDisable__I
  (JNIEnv *_env, jobject _this, jint cap) {
    glDisable(
        (GLenum)cap
    );
}

/* void glDisableClientState ( GLenum array ) */
static void
android_glDisableClientState__I
  (JNIEnv *_env, jobject _this, jint array) {
    glDisableClientState(
        (GLenum)array
    );
}

/* void glDrawArrays ( GLenum mode, GLint first, GLsizei count ) */
static void
android_glDrawArrays__III
  (JNIEnv *_env, jobject _this, jint mode, jint first, jint count) {
    glDrawArrays(
        (GLenum)mode,
        (GLint)first,
        (GLsizei)count
    );
}

/* void glDrawElements ( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices ) */
static void
android_glDrawElements__IIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint mode, jint count, jint type, jobject indices_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *indices = (GLvoid *) 0;

    indices = (GLvoid *)getPointer(_env, indices_buf, &_array, &_remaining);
    if (_remaining < count) {
        _env->ThrowNew(AIOOBEClass, "remaining() < count");
        goto exit;
    }
    glDrawElements(
        (GLenum)mode,
        (GLsizei)count,
        (GLenum)type,
        (GLvoid *)indices
    );

exit:
    if (_array) {
        releasePointer(_env, _array, indices, JNI_FALSE);
    }
}

/* void glEnable ( GLenum cap ) */
static void
android_glEnable__I
  (JNIEnv *_env, jobject _this, jint cap) {
    glEnable(
        (GLenum)cap
    );
}

/* void glEnableClientState ( GLenum array ) */
static void
android_glEnableClientState__I
  (JNIEnv *_env, jobject _this, jint array) {
    glEnableClientState(
        (GLenum)array
    );
}

/* void glFinish ( void ) */
static void
android_glFinish__
  (JNIEnv *_env, jobject _this) {
    glFinish();
}

/* void glFlush ( void ) */
static void
android_glFlush__
  (JNIEnv *_env, jobject _this) {
    glFlush();
}

/* void glFogf ( GLenum pname, GLfloat param ) */
static void
android_glFogf__IF
  (JNIEnv *_env, jobject _this, jint pname, jfloat param) {
    glFogf(
        (GLenum)pname,
        (GLfloat)param
    );
}

/* void glFogfv ( GLenum pname, const GLfloat *params ) */
static void
android_glFogfv__I_3FI
  (JNIEnv *_env, jobject _this, jint pname, jfloatArray params_ref, jint offset) {
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_FOG_MODE)
        case GL_FOG_MODE:
#endif // defined(GL_FOG_MODE)
#if defined(GL_FOG_DENSITY)
        case GL_FOG_DENSITY:
#endif // defined(GL_FOG_DENSITY)
#if defined(GL_FOG_START)
        case GL_FOG_START:
#endif // defined(GL_FOG_START)
#if defined(GL_FOG_END)
        case GL_FOG_END:
#endif // defined(GL_FOG_END)
            _needed = 1;
            break;
#if defined(GL_FOG_COLOR)
        case GL_FOG_COLOR:
#endif // defined(GL_FOG_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glFogfv(
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glFogfv ( GLenum pname, const GLfloat *params ) */
static void
android_glFogfv__ILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_FOG_MODE)
        case GL_FOG_MODE:
#endif // defined(GL_FOG_MODE)
#if defined(GL_FOG_DENSITY)
        case GL_FOG_DENSITY:
#endif // defined(GL_FOG_DENSITY)
#if defined(GL_FOG_START)
        case GL_FOG_START:
#endif // defined(GL_FOG_START)
#if defined(GL_FOG_END)
        case GL_FOG_END:
#endif // defined(GL_FOG_END)
            _needed = 1;
            break;
#if defined(GL_FOG_COLOR)
        case GL_FOG_COLOR:
#endif // defined(GL_FOG_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glFogfv(
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glFogx ( GLenum pname, GLfixed param ) */
static void
android_glFogx__II
  (JNIEnv *_env, jobject _this, jint pname, jint param) {
    glFogx(
        (GLenum)pname,
        (GLfixed)param
    );
}

/* void glFogxv ( GLenum pname, const GLfixed *params ) */
static void
android_glFogxv__I_3II
  (JNIEnv *_env, jobject _this, jint pname, jintArray params_ref, jint offset) {
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_FOG_MODE)
        case GL_FOG_MODE:
#endif // defined(GL_FOG_MODE)
#if defined(GL_FOG_DENSITY)
        case GL_FOG_DENSITY:
#endif // defined(GL_FOG_DENSITY)
#if defined(GL_FOG_START)
        case GL_FOG_START:
#endif // defined(GL_FOG_START)
#if defined(GL_FOG_END)
        case GL_FOG_END:
#endif // defined(GL_FOG_END)
            _needed = 1;
            break;
#if defined(GL_FOG_COLOR)
        case GL_FOG_COLOR:
#endif // defined(GL_FOG_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glFogxv(
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glFogxv ( GLenum pname, const GLfixed *params ) */
static void
android_glFogxv__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_FOG_MODE)
        case GL_FOG_MODE:
#endif // defined(GL_FOG_MODE)
#if defined(GL_FOG_DENSITY)
        case GL_FOG_DENSITY:
#endif // defined(GL_FOG_DENSITY)
#if defined(GL_FOG_START)
        case GL_FOG_START:
#endif // defined(GL_FOG_START)
#if defined(GL_FOG_END)
        case GL_FOG_END:
#endif // defined(GL_FOG_END)
            _needed = 1;
            break;
#if defined(GL_FOG_COLOR)
        case GL_FOG_COLOR:
#endif // defined(GL_FOG_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glFogxv(
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glFrontFace ( GLenum mode ) */
static void
android_glFrontFace__I
  (JNIEnv *_env, jobject _this, jint mode) {
    glFrontFace(
        (GLenum)mode
    );
}

/* void glFrustumf ( GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar ) */
static void
android_glFrustumf__FFFFFF
  (JNIEnv *_env, jobject _this, jfloat left, jfloat right, jfloat bottom, jfloat top, jfloat zNear, jfloat zFar) {
    glFrustumf(
        (GLfloat)left,
        (GLfloat)right,
        (GLfloat)bottom,
        (GLfloat)top,
        (GLfloat)zNear,
        (GLfloat)zFar
    );
}

/* void glFrustumx ( GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar ) */
static void
android_glFrustumx__IIIIII
  (JNIEnv *_env, jobject _this, jint left, jint right, jint bottom, jint top, jint zNear, jint zFar) {
    glFrustumx(
        (GLfixed)left,
        (GLfixed)right,
        (GLfixed)bottom,
        (GLfixed)top,
        (GLfixed)zNear,
        (GLfixed)zFar
    );
}

/* void glGenTextures ( GLsizei n, GLuint *textures ) */
static void
android_glGenTextures__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray textures_ref, jint offset) {
    jint _exception = 0;
    GLuint *textures_base = (GLuint *) 0;
    jint _remaining;
    GLuint *textures = (GLuint *) 0;

    if (!textures_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "textures == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(textures_ref) - offset;
    if (_remaining < n) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < n");
        goto exit;
    }
    textures_base = (GLuint *)
        _env->GetPrimitiveArrayCritical(textures_ref, (jboolean *)0);
    textures = textures_base + offset;

    glGenTextures(
        (GLsizei)n,
        (GLuint *)textures
    );

exit:
    if (textures_base) {
        _env->ReleasePrimitiveArrayCritical(textures_ref, textures_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGenTextures ( GLsizei n, GLuint *textures ) */
static void
android_glGenTextures__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject textures_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLuint *textures = (GLuint *) 0;

    textures = (GLuint *)getPointer(_env, textures_buf, &_array, &_remaining);
    if (_remaining < n) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < n");
        goto exit;
    }
    glGenTextures(
        (GLsizei)n,
        (GLuint *)textures
    );

exit:
    if (_array) {
        releasePointer(_env, _array, textures, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* GLenum glGetError ( void ) */
static jint
android_glGetError__
  (JNIEnv *_env, jobject _this) {
    GLenum _returnValue;
    _returnValue = glGetError();
    return _returnValue;
}

/* void glGetIntegerv ( GLenum pname, GLint *params ) */
static void
android_glGetIntegerv__I_3II
  (JNIEnv *_env, jobject _this, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLint *params_base = (GLint *) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_ALPHA_BITS)
        case GL_ALPHA_BITS:
#endif // defined(GL_ALPHA_BITS)
#if defined(GL_ALPHA_TEST_FUNC)
        case GL_ALPHA_TEST_FUNC:
#endif // defined(GL_ALPHA_TEST_FUNC)
#if defined(GL_ALPHA_TEST_REF)
        case GL_ALPHA_TEST_REF:
#endif // defined(GL_ALPHA_TEST_REF)
#if defined(GL_BLEND_DST)
        case GL_BLEND_DST:
#endif // defined(GL_BLEND_DST)
#if defined(GL_BLUE_BITS)
        case GL_BLUE_BITS:
#endif // defined(GL_BLUE_BITS)
#if defined(GL_COLOR_ARRAY_BUFFER_BINDING)
        case GL_COLOR_ARRAY_BUFFER_BINDING:
#endif // defined(GL_COLOR_ARRAY_BUFFER_BINDING)
#if defined(GL_COLOR_ARRAY_SIZE)
        case GL_COLOR_ARRAY_SIZE:
#endif // defined(GL_COLOR_ARRAY_SIZE)
#if defined(GL_COLOR_ARRAY_STRIDE)
        case GL_COLOR_ARRAY_STRIDE:
#endif // defined(GL_COLOR_ARRAY_STRIDE)
#if defined(GL_COLOR_ARRAY_TYPE)
        case GL_COLOR_ARRAY_TYPE:
#endif // defined(GL_COLOR_ARRAY_TYPE)
#if defined(GL_CULL_FACE)
        case GL_CULL_FACE:
#endif // defined(GL_CULL_FACE)
#if defined(GL_DEPTH_BITS)
        case GL_DEPTH_BITS:
#endif // defined(GL_DEPTH_BITS)
#if defined(GL_DEPTH_CLEAR_VALUE)
        case GL_DEPTH_CLEAR_VALUE:
#endif // defined(GL_DEPTH_CLEAR_VALUE)
#if defined(GL_DEPTH_FUNC)
        case GL_DEPTH_FUNC:
#endif // defined(GL_DEPTH_FUNC)
#if defined(GL_DEPTH_WRITEMASK)
        case GL_DEPTH_WRITEMASK:
#endif // defined(GL_DEPTH_WRITEMASK)
#if defined(GL_FOG_DENSITY)
        case GL_FOG_DENSITY:
#endif // defined(GL_FOG_DENSITY)
#if defined(GL_FOG_END)
        case GL_FOG_END:
#endif // defined(GL_FOG_END)
#if defined(GL_FOG_MODE)
        case GL_FOG_MODE:
#endif // defined(GL_FOG_MODE)
#if defined(GL_FOG_START)
        case GL_FOG_START:
#endif // defined(GL_FOG_START)
#if defined(GL_FRONT_FACE)
        case GL_FRONT_FACE:
#endif // defined(GL_FRONT_FACE)
#if defined(GL_GREEN_BITS)
        case GL_GREEN_BITS:
#endif // defined(GL_GREEN_BITS)
#if defined(GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES)
        case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
#endif // defined(GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES)
#if defined(GL_IMPLEMENTATION_COLOR_READ_TYPE_OES)
        case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
#endif // defined(GL_IMPLEMENTATION_COLOR_READ_TYPE_OES)
#if defined(GL_LIGHT_MODEL_COLOR_CONTROL)
        case GL_LIGHT_MODEL_COLOR_CONTROL:
#endif // defined(GL_LIGHT_MODEL_COLOR_CONTROL)
#if defined(GL_LIGHT_MODEL_LOCAL_VIEWER)
        case GL_LIGHT_MODEL_LOCAL_VIEWER:
#endif // defined(GL_LIGHT_MODEL_LOCAL_VIEWER)
#if defined(GL_LIGHT_MODEL_TWO_SIDE)
        case GL_LIGHT_MODEL_TWO_SIDE:
#endif // defined(GL_LIGHT_MODEL_TWO_SIDE)
#if defined(GL_LINE_SMOOTH_HINT)
        case GL_LINE_SMOOTH_HINT:
#endif // defined(GL_LINE_SMOOTH_HINT)
#if defined(GL_LINE_WIDTH)
        case GL_LINE_WIDTH:
#endif // defined(GL_LINE_WIDTH)
#if defined(GL_LOGIC_OP_MODE)
        case GL_LOGIC_OP_MODE:
#endif // defined(GL_LOGIC_OP_MODE)
#if defined(GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES)
        case GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES)
#if defined(GL_MATRIX_INDEX_ARRAY_SIZE_OES)
        case GL_MATRIX_INDEX_ARRAY_SIZE_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_SIZE_OES)
#if defined(GL_MATRIX_INDEX_ARRAY_STRIDE_OES)
        case GL_MATRIX_INDEX_ARRAY_STRIDE_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_STRIDE_OES)
#if defined(GL_MATRIX_INDEX_ARRAY_TYPE_OES)
        case GL_MATRIX_INDEX_ARRAY_TYPE_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_TYPE_OES)
#if defined(GL_MATRIX_MODE)
        case GL_MATRIX_MODE:
#endif // defined(GL_MATRIX_MODE)
#if defined(GL_MAX_CLIP_PLANES)
        case GL_MAX_CLIP_PLANES:
#endif // defined(GL_MAX_CLIP_PLANES)
#if defined(GL_MAX_ELEMENTS_INDICES)
        case GL_MAX_ELEMENTS_INDICES:
#endif // defined(GL_MAX_ELEMENTS_INDICES)
#if defined(GL_MAX_ELEMENTS_VERTICES)
        case GL_MAX_ELEMENTS_VERTICES:
#endif // defined(GL_MAX_ELEMENTS_VERTICES)
#if defined(GL_MAX_LIGHTS)
        case GL_MAX_LIGHTS:
#endif // defined(GL_MAX_LIGHTS)
#if defined(GL_MAX_MODELVIEW_STACK_DEPTH)
        case GL_MAX_MODELVIEW_STACK_DEPTH:
#endif // defined(GL_MAX_MODELVIEW_STACK_DEPTH)
#if defined(GL_MAX_PALETTE_MATRICES_OES)
        case GL_MAX_PALETTE_MATRICES_OES:
#endif // defined(GL_MAX_PALETTE_MATRICES_OES)
#if defined(GL_MAX_PROJECTION_STACK_DEPTH)
        case GL_MAX_PROJECTION_STACK_DEPTH:
#endif // defined(GL_MAX_PROJECTION_STACK_DEPTH)
#if defined(GL_MAX_TEXTURE_SIZE)
        case GL_MAX_TEXTURE_SIZE:
#endif // defined(GL_MAX_TEXTURE_SIZE)
#if defined(GL_MAX_TEXTURE_STACK_DEPTH)
        case GL_MAX_TEXTURE_STACK_DEPTH:
#endif // defined(GL_MAX_TEXTURE_STACK_DEPTH)
#if defined(GL_MAX_TEXTURE_UNITS)
        case GL_MAX_TEXTURE_UNITS:
#endif // defined(GL_MAX_TEXTURE_UNITS)
#if defined(GL_MAX_VERTEX_UNITS_OES)
        case GL_MAX_VERTEX_UNITS_OES:
#endif // defined(GL_MAX_VERTEX_UNITS_OES)
#if defined(GL_MODELVIEW_STACK_DEPTH)
        case GL_MODELVIEW_STACK_DEPTH:
#endif // defined(GL_MODELVIEW_STACK_DEPTH)
#if defined(GL_NORMAL_ARRAY_BUFFER_BINDING)
        case GL_NORMAL_ARRAY_BUFFER_BINDING:
#endif // defined(GL_NORMAL_ARRAY_BUFFER_BINDING)
#if defined(GL_NORMAL_ARRAY_STRIDE)
        case GL_NORMAL_ARRAY_STRIDE:
#endif // defined(GL_NORMAL_ARRAY_STRIDE)
#if defined(GL_NORMAL_ARRAY_TYPE)
        case GL_NORMAL_ARRAY_TYPE:
#endif // defined(GL_NORMAL_ARRAY_TYPE)
#if defined(GL_NUM_COMPRESSED_TEXTURE_FORMATS)
        case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
#endif // defined(GL_NUM_COMPRESSED_TEXTURE_FORMATS)
#if defined(GL_PACK_ALIGNMENT)
        case GL_PACK_ALIGNMENT:
#endif // defined(GL_PACK_ALIGNMENT)
#if defined(GL_PERSPECTIVE_CORRECTION_HINT)
        case GL_PERSPECTIVE_CORRECTION_HINT:
#endif // defined(GL_PERSPECTIVE_CORRECTION_HINT)
#if defined(GL_POINT_SIZE)
        case GL_POINT_SIZE:
#endif // defined(GL_POINT_SIZE)
#if defined(GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES)
        case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
#endif // defined(GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES)
#if defined(GL_POINT_SIZE_ARRAY_STRIDE_OES)
        case GL_POINT_SIZE_ARRAY_STRIDE_OES:
#endif // defined(GL_POINT_SIZE_ARRAY_STRIDE_OES)
#if defined(GL_POINT_SIZE_ARRAY_TYPE_OES)
        case GL_POINT_SIZE_ARRAY_TYPE_OES:
#endif // defined(GL_POINT_SIZE_ARRAY_TYPE_OES)
#if defined(GL_POINT_SMOOTH_HINT)
        case GL_POINT_SMOOTH_HINT:
#endif // defined(GL_POINT_SMOOTH_HINT)
#if defined(GL_POLYGON_OFFSET_FACTOR)
        case GL_POLYGON_OFFSET_FACTOR:
#endif // defined(GL_POLYGON_OFFSET_FACTOR)
#if defined(GL_POLYGON_OFFSET_UNITS)
        case GL_POLYGON_OFFSET_UNITS:
#endif // defined(GL_POLYGON_OFFSET_UNITS)
#if defined(GL_PROJECTION_STACK_DEPTH)
        case GL_PROJECTION_STACK_DEPTH:
#endif // defined(GL_PROJECTION_STACK_DEPTH)
#if defined(GL_RED_BITS)
        case GL_RED_BITS:
#endif // defined(GL_RED_BITS)
#if defined(GL_SHADE_MODEL)
        case GL_SHADE_MODEL:
#endif // defined(GL_SHADE_MODEL)
#if defined(GL_STENCIL_BITS)
        case GL_STENCIL_BITS:
#endif // defined(GL_STENCIL_BITS)
#if defined(GL_STENCIL_CLEAR_VALUE)
        case GL_STENCIL_CLEAR_VALUE:
#endif // defined(GL_STENCIL_CLEAR_VALUE)
#if defined(GL_STENCIL_FAIL)
        case GL_STENCIL_FAIL:
#endif // defined(GL_STENCIL_FAIL)
#if defined(GL_STENCIL_FUNC)
        case GL_STENCIL_FUNC:
#endif // defined(GL_STENCIL_FUNC)
#if defined(GL_STENCIL_PASS_DEPTH_FAIL)
        case GL_STENCIL_PASS_DEPTH_FAIL:
#endif // defined(GL_STENCIL_PASS_DEPTH_FAIL)
#if defined(GL_STENCIL_PASS_DEPTH_PASS)
        case GL_STENCIL_PASS_DEPTH_PASS:
#endif // defined(GL_STENCIL_PASS_DEPTH_PASS)
#if defined(GL_STENCIL_REF)
        case GL_STENCIL_REF:
#endif // defined(GL_STENCIL_REF)
#if defined(GL_STENCIL_VALUE_MASK)
        case GL_STENCIL_VALUE_MASK:
#endif // defined(GL_STENCIL_VALUE_MASK)
#if defined(GL_STENCIL_WRITEMASK)
        case GL_STENCIL_WRITEMASK:
#endif // defined(GL_STENCIL_WRITEMASK)
#if defined(GL_SUBPIXEL_BITS)
        case GL_SUBPIXEL_BITS:
#endif // defined(GL_SUBPIXEL_BITS)
#if defined(GL_TEXTURE_BINDING_2D)
        case GL_TEXTURE_BINDING_2D:
#endif // defined(GL_TEXTURE_BINDING_2D)
#if defined(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING)
        case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
#endif // defined(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING)
#if defined(GL_TEXTURE_COORD_ARRAY_SIZE)
        case GL_TEXTURE_COORD_ARRAY_SIZE:
#endif // defined(GL_TEXTURE_COORD_ARRAY_SIZE)
#if defined(GL_TEXTURE_COORD_ARRAY_STRIDE)
        case GL_TEXTURE_COORD_ARRAY_STRIDE:
#endif // defined(GL_TEXTURE_COORD_ARRAY_STRIDE)
#if defined(GL_TEXTURE_COORD_ARRAY_TYPE)
        case GL_TEXTURE_COORD_ARRAY_TYPE:
#endif // defined(GL_TEXTURE_COORD_ARRAY_TYPE)
#if defined(GL_TEXTURE_STACK_DEPTH)
        case GL_TEXTURE_STACK_DEPTH:
#endif // defined(GL_TEXTURE_STACK_DEPTH)
#if defined(GL_UNPACK_ALIGNMENT)
        case GL_UNPACK_ALIGNMENT:
#endif // defined(GL_UNPACK_ALIGNMENT)
#if defined(GL_VERTEX_ARRAY_BUFFER_BINDING)
        case GL_VERTEX_ARRAY_BUFFER_BINDING:
#endif // defined(GL_VERTEX_ARRAY_BUFFER_BINDING)
#if defined(GL_VERTEX_ARRAY_SIZE)
        case GL_VERTEX_ARRAY_SIZE:
#endif // defined(GL_VERTEX_ARRAY_SIZE)
#if defined(GL_VERTEX_ARRAY_STRIDE)
        case GL_VERTEX_ARRAY_STRIDE:
#endif // defined(GL_VERTEX_ARRAY_STRIDE)
#if defined(GL_VERTEX_ARRAY_TYPE)
        case GL_VERTEX_ARRAY_TYPE:
#endif // defined(GL_VERTEX_ARRAY_TYPE)
#if defined(GL_WEIGHT_ARRAY_BUFFER_BINDING_OES)
        case GL_WEIGHT_ARRAY_BUFFER_BINDING_OES:
#endif // defined(GL_WEIGHT_ARRAY_BUFFER_BINDING_OES)
#if defined(GL_WEIGHT_ARRAY_SIZE_OES)
        case GL_WEIGHT_ARRAY_SIZE_OES:
#endif // defined(GL_WEIGHT_ARRAY_SIZE_OES)
#if defined(GL_WEIGHT_ARRAY_STRIDE_OES)
        case GL_WEIGHT_ARRAY_STRIDE_OES:
#endif // defined(GL_WEIGHT_ARRAY_STRIDE_OES)
#if defined(GL_WEIGHT_ARRAY_TYPE_OES)
        case GL_WEIGHT_ARRAY_TYPE_OES:
#endif // defined(GL_WEIGHT_ARRAY_TYPE_OES)
            _needed = 1;
            break;
#if defined(GL_ALIASED_POINT_SIZE_RANGE)
        case GL_ALIASED_POINT_SIZE_RANGE:
#endif // defined(GL_ALIASED_POINT_SIZE_RANGE)
#if defined(GL_ALIASED_LINE_WIDTH_RANGE)
        case GL_ALIASED_LINE_WIDTH_RANGE:
#endif // defined(GL_ALIASED_LINE_WIDTH_RANGE)
#if defined(GL_DEPTH_RANGE)
        case GL_DEPTH_RANGE:
#endif // defined(GL_DEPTH_RANGE)
#if defined(GL_MAX_VIEWPORT_DIMS)
        case GL_MAX_VIEWPORT_DIMS:
#endif // defined(GL_MAX_VIEWPORT_DIMS)
#if defined(GL_SMOOTH_LINE_WIDTH_RANGE)
        case GL_SMOOTH_LINE_WIDTH_RANGE:
#endif // defined(GL_SMOOTH_LINE_WIDTH_RANGE)
#if defined(GL_SMOOTH_POINT_SIZE_RANGE)
        case GL_SMOOTH_POINT_SIZE_RANGE:
#endif // defined(GL_SMOOTH_POINT_SIZE_RANGE)
            _needed = 2;
            break;
#if defined(GL_COLOR_CLEAR_VALUE)
        case GL_COLOR_CLEAR_VALUE:
#endif // defined(GL_COLOR_CLEAR_VALUE)
#if defined(GL_COLOR_WRITEMASK)
        case GL_COLOR_WRITEMASK:
#endif // defined(GL_COLOR_WRITEMASK)
#if defined(GL_FOG_COLOR)
        case GL_FOG_COLOR:
#endif // defined(GL_FOG_COLOR)
#if defined(GL_LIGHT_MODEL_AMBIENT)
        case GL_LIGHT_MODEL_AMBIENT:
#endif // defined(GL_LIGHT_MODEL_AMBIENT)
#if defined(GL_SCISSOR_BOX)
        case GL_SCISSOR_BOX:
#endif // defined(GL_SCISSOR_BOX)
#if defined(GL_VIEWPORT)
        case GL_VIEWPORT:
#endif // defined(GL_VIEWPORT)
            _needed = 4;
            break;
#if defined(GL_MODELVIEW_MATRIX)
        case GL_MODELVIEW_MATRIX:
#endif // defined(GL_MODELVIEW_MATRIX)
#if defined(GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES)
        case GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES:
#endif // defined(GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES)
#if defined(GL_PROJECTION_MATRIX)
        case GL_PROJECTION_MATRIX:
#endif // defined(GL_PROJECTION_MATRIX)
#if defined(GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES)
        case GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES:
#endif // defined(GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES)
#if defined(GL_TEXTURE_MATRIX)
        case GL_TEXTURE_MATRIX:
#endif // defined(GL_TEXTURE_MATRIX)
#if defined(GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES)
        case GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES:
#endif // defined(GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES)
            _needed = 16;
            break;
#if defined(GL_COMPRESSED_TEXTURE_FORMATS)
        case GL_COMPRESSED_TEXTURE_FORMATS:
#endif // defined(GL_COMPRESSED_TEXTURE_FORMATS)
            _needed = getNumCompressedTextureFormats();
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLint *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetIntegerv(
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetIntegerv ( GLenum pname, GLint *params ) */
static void
android_glGetIntegerv__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    params = (GLint *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_ALPHA_BITS)
        case GL_ALPHA_BITS:
#endif // defined(GL_ALPHA_BITS)
#if defined(GL_ALPHA_TEST_FUNC)
        case GL_ALPHA_TEST_FUNC:
#endif // defined(GL_ALPHA_TEST_FUNC)
#if defined(GL_ALPHA_TEST_REF)
        case GL_ALPHA_TEST_REF:
#endif // defined(GL_ALPHA_TEST_REF)
#if defined(GL_BLEND_DST)
        case GL_BLEND_DST:
#endif // defined(GL_BLEND_DST)
#if defined(GL_BLUE_BITS)
        case GL_BLUE_BITS:
#endif // defined(GL_BLUE_BITS)
#if defined(GL_COLOR_ARRAY_BUFFER_BINDING)
        case GL_COLOR_ARRAY_BUFFER_BINDING:
#endif // defined(GL_COLOR_ARRAY_BUFFER_BINDING)
#if defined(GL_COLOR_ARRAY_SIZE)
        case GL_COLOR_ARRAY_SIZE:
#endif // defined(GL_COLOR_ARRAY_SIZE)
#if defined(GL_COLOR_ARRAY_STRIDE)
        case GL_COLOR_ARRAY_STRIDE:
#endif // defined(GL_COLOR_ARRAY_STRIDE)
#if defined(GL_COLOR_ARRAY_TYPE)
        case GL_COLOR_ARRAY_TYPE:
#endif // defined(GL_COLOR_ARRAY_TYPE)
#if defined(GL_CULL_FACE)
        case GL_CULL_FACE:
#endif // defined(GL_CULL_FACE)
#if defined(GL_DEPTH_BITS)
        case GL_DEPTH_BITS:
#endif // defined(GL_DEPTH_BITS)
#if defined(GL_DEPTH_CLEAR_VALUE)
        case GL_DEPTH_CLEAR_VALUE:
#endif // defined(GL_DEPTH_CLEAR_VALUE)
#if defined(GL_DEPTH_FUNC)
        case GL_DEPTH_FUNC:
#endif // defined(GL_DEPTH_FUNC)
#if defined(GL_DEPTH_WRITEMASK)
        case GL_DEPTH_WRITEMASK:
#endif // defined(GL_DEPTH_WRITEMASK)
#if defined(GL_FOG_DENSITY)
        case GL_FOG_DENSITY:
#endif // defined(GL_FOG_DENSITY)
#if defined(GL_FOG_END)
        case GL_FOG_END:
#endif // defined(GL_FOG_END)
#if defined(GL_FOG_MODE)
        case GL_FOG_MODE:
#endif // defined(GL_FOG_MODE)
#if defined(GL_FOG_START)
        case GL_FOG_START:
#endif // defined(GL_FOG_START)
#if defined(GL_FRONT_FACE)
        case GL_FRONT_FACE:
#endif // defined(GL_FRONT_FACE)
#if defined(GL_GREEN_BITS)
        case GL_GREEN_BITS:
#endif // defined(GL_GREEN_BITS)
#if defined(GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES)
        case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
#endif // defined(GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES)
#if defined(GL_IMPLEMENTATION_COLOR_READ_TYPE_OES)
        case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
#endif // defined(GL_IMPLEMENTATION_COLOR_READ_TYPE_OES)
#if defined(GL_LIGHT_MODEL_COLOR_CONTROL)
        case GL_LIGHT_MODEL_COLOR_CONTROL:
#endif // defined(GL_LIGHT_MODEL_COLOR_CONTROL)
#if defined(GL_LIGHT_MODEL_LOCAL_VIEWER)
        case GL_LIGHT_MODEL_LOCAL_VIEWER:
#endif // defined(GL_LIGHT_MODEL_LOCAL_VIEWER)
#if defined(GL_LIGHT_MODEL_TWO_SIDE)
        case GL_LIGHT_MODEL_TWO_SIDE:
#endif // defined(GL_LIGHT_MODEL_TWO_SIDE)
#if defined(GL_LINE_SMOOTH_HINT)
        case GL_LINE_SMOOTH_HINT:
#endif // defined(GL_LINE_SMOOTH_HINT)
#if defined(GL_LINE_WIDTH)
        case GL_LINE_WIDTH:
#endif // defined(GL_LINE_WIDTH)
#if defined(GL_LOGIC_OP_MODE)
        case GL_LOGIC_OP_MODE:
#endif // defined(GL_LOGIC_OP_MODE)
#if defined(GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES)
        case GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES)
#if defined(GL_MATRIX_INDEX_ARRAY_SIZE_OES)
        case GL_MATRIX_INDEX_ARRAY_SIZE_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_SIZE_OES)
#if defined(GL_MATRIX_INDEX_ARRAY_STRIDE_OES)
        case GL_MATRIX_INDEX_ARRAY_STRIDE_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_STRIDE_OES)
#if defined(GL_MATRIX_INDEX_ARRAY_TYPE_OES)
        case GL_MATRIX_INDEX_ARRAY_TYPE_OES:
#endif // defined(GL_MATRIX_INDEX_ARRAY_TYPE_OES)
#if defined(GL_MATRIX_MODE)
        case GL_MATRIX_MODE:
#endif // defined(GL_MATRIX_MODE)
#if defined(GL_MAX_CLIP_PLANES)
        case GL_MAX_CLIP_PLANES:
#endif // defined(GL_MAX_CLIP_PLANES)
#if defined(GL_MAX_ELEMENTS_INDICES)
        case GL_MAX_ELEMENTS_INDICES:
#endif // defined(GL_MAX_ELEMENTS_INDICES)
#if defined(GL_MAX_ELEMENTS_VERTICES)
        case GL_MAX_ELEMENTS_VERTICES:
#endif // defined(GL_MAX_ELEMENTS_VERTICES)
#if defined(GL_MAX_LIGHTS)
        case GL_MAX_LIGHTS:
#endif // defined(GL_MAX_LIGHTS)
#if defined(GL_MAX_MODELVIEW_STACK_DEPTH)
        case GL_MAX_MODELVIEW_STACK_DEPTH:
#endif // defined(GL_MAX_MODELVIEW_STACK_DEPTH)
#if defined(GL_MAX_PALETTE_MATRICES_OES)
        case GL_MAX_PALETTE_MATRICES_OES:
#endif // defined(GL_MAX_PALETTE_MATRICES_OES)
#if defined(GL_MAX_PROJECTION_STACK_DEPTH)
        case GL_MAX_PROJECTION_STACK_DEPTH:
#endif // defined(GL_MAX_PROJECTION_STACK_DEPTH)
#if defined(GL_MAX_TEXTURE_SIZE)
        case GL_MAX_TEXTURE_SIZE:
#endif // defined(GL_MAX_TEXTURE_SIZE)
#if defined(GL_MAX_TEXTURE_STACK_DEPTH)
        case GL_MAX_TEXTURE_STACK_DEPTH:
#endif // defined(GL_MAX_TEXTURE_STACK_DEPTH)
#if defined(GL_MAX_TEXTURE_UNITS)
        case GL_MAX_TEXTURE_UNITS:
#endif // defined(GL_MAX_TEXTURE_UNITS)
#if defined(GL_MAX_VERTEX_UNITS_OES)
        case GL_MAX_VERTEX_UNITS_OES:
#endif // defined(GL_MAX_VERTEX_UNITS_OES)
#if defined(GL_MODELVIEW_STACK_DEPTH)
        case GL_MODELVIEW_STACK_DEPTH:
#endif // defined(GL_MODELVIEW_STACK_DEPTH)
#if defined(GL_NORMAL_ARRAY_BUFFER_BINDING)
        case GL_NORMAL_ARRAY_BUFFER_BINDING:
#endif // defined(GL_NORMAL_ARRAY_BUFFER_BINDING)
#if defined(GL_NORMAL_ARRAY_STRIDE)
        case GL_NORMAL_ARRAY_STRIDE:
#endif // defined(GL_NORMAL_ARRAY_STRIDE)
#if defined(GL_NORMAL_ARRAY_TYPE)
        case GL_NORMAL_ARRAY_TYPE:
#endif // defined(GL_NORMAL_ARRAY_TYPE)
#if defined(GL_NUM_COMPRESSED_TEXTURE_FORMATS)
        case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
#endif // defined(GL_NUM_COMPRESSED_TEXTURE_FORMATS)
#if defined(GL_PACK_ALIGNMENT)
        case GL_PACK_ALIGNMENT:
#endif // defined(GL_PACK_ALIGNMENT)
#if defined(GL_PERSPECTIVE_CORRECTION_HINT)
        case GL_PERSPECTIVE_CORRECTION_HINT:
#endif // defined(GL_PERSPECTIVE_CORRECTION_HINT)
#if defined(GL_POINT_SIZE)
        case GL_POINT_SIZE:
#endif // defined(GL_POINT_SIZE)
#if defined(GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES)
        case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
#endif // defined(GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES)
#if defined(GL_POINT_SIZE_ARRAY_STRIDE_OES)
        case GL_POINT_SIZE_ARRAY_STRIDE_OES:
#endif // defined(GL_POINT_SIZE_ARRAY_STRIDE_OES)
#if defined(GL_POINT_SIZE_ARRAY_TYPE_OES)
        case GL_POINT_SIZE_ARRAY_TYPE_OES:
#endif // defined(GL_POINT_SIZE_ARRAY_TYPE_OES)
#if defined(GL_POINT_SMOOTH_HINT)
        case GL_POINT_SMOOTH_HINT:
#endif // defined(GL_POINT_SMOOTH_HINT)
#if defined(GL_POLYGON_OFFSET_FACTOR)
        case GL_POLYGON_OFFSET_FACTOR:
#endif // defined(GL_POLYGON_OFFSET_FACTOR)
#if defined(GL_POLYGON_OFFSET_UNITS)
        case GL_POLYGON_OFFSET_UNITS:
#endif // defined(GL_POLYGON_OFFSET_UNITS)
#if defined(GL_PROJECTION_STACK_DEPTH)
        case GL_PROJECTION_STACK_DEPTH:
#endif // defined(GL_PROJECTION_STACK_DEPTH)
#if defined(GL_RED_BITS)
        case GL_RED_BITS:
#endif // defined(GL_RED_BITS)
#if defined(GL_SHADE_MODEL)
        case GL_SHADE_MODEL:
#endif // defined(GL_SHADE_MODEL)
#if defined(GL_STENCIL_BITS)
        case GL_STENCIL_BITS:
#endif // defined(GL_STENCIL_BITS)
#if defined(GL_STENCIL_CLEAR_VALUE)
        case GL_STENCIL_CLEAR_VALUE:
#endif // defined(GL_STENCIL_CLEAR_VALUE)
#if defined(GL_STENCIL_FAIL)
        case GL_STENCIL_FAIL:
#endif // defined(GL_STENCIL_FAIL)
#if defined(GL_STENCIL_FUNC)
        case GL_STENCIL_FUNC:
#endif // defined(GL_STENCIL_FUNC)
#if defined(GL_STENCIL_PASS_DEPTH_FAIL)
        case GL_STENCIL_PASS_DEPTH_FAIL:
#endif // defined(GL_STENCIL_PASS_DEPTH_FAIL)
#if defined(GL_STENCIL_PASS_DEPTH_PASS)
        case GL_STENCIL_PASS_DEPTH_PASS:
#endif // defined(GL_STENCIL_PASS_DEPTH_PASS)
#if defined(GL_STENCIL_REF)
        case GL_STENCIL_REF:
#endif // defined(GL_STENCIL_REF)
#if defined(GL_STENCIL_VALUE_MASK)
        case GL_STENCIL_VALUE_MASK:
#endif // defined(GL_STENCIL_VALUE_MASK)
#if defined(GL_STENCIL_WRITEMASK)
        case GL_STENCIL_WRITEMASK:
#endif // defined(GL_STENCIL_WRITEMASK)
#if defined(GL_SUBPIXEL_BITS)
        case GL_SUBPIXEL_BITS:
#endif // defined(GL_SUBPIXEL_BITS)
#if defined(GL_TEXTURE_BINDING_2D)
        case GL_TEXTURE_BINDING_2D:
#endif // defined(GL_TEXTURE_BINDING_2D)
#if defined(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING)
        case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
#endif // defined(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING)
#if defined(GL_TEXTURE_COORD_ARRAY_SIZE)
        case GL_TEXTURE_COORD_ARRAY_SIZE:
#endif // defined(GL_TEXTURE_COORD_ARRAY_SIZE)
#if defined(GL_TEXTURE_COORD_ARRAY_STRIDE)
        case GL_TEXTURE_COORD_ARRAY_STRIDE:
#endif // defined(GL_TEXTURE_COORD_ARRAY_STRIDE)
#if defined(GL_TEXTURE_COORD_ARRAY_TYPE)
        case GL_TEXTURE_COORD_ARRAY_TYPE:
#endif // defined(GL_TEXTURE_COORD_ARRAY_TYPE)
#if defined(GL_TEXTURE_STACK_DEPTH)
        case GL_TEXTURE_STACK_DEPTH:
#endif // defined(GL_TEXTURE_STACK_DEPTH)
#if defined(GL_UNPACK_ALIGNMENT)
        case GL_UNPACK_ALIGNMENT:
#endif // defined(GL_UNPACK_ALIGNMENT)
#if defined(GL_VERTEX_ARRAY_BUFFER_BINDING)
        case GL_VERTEX_ARRAY_BUFFER_BINDING:
#endif // defined(GL_VERTEX_ARRAY_BUFFER_BINDING)
#if defined(GL_VERTEX_ARRAY_SIZE)
        case GL_VERTEX_ARRAY_SIZE:
#endif // defined(GL_VERTEX_ARRAY_SIZE)
#if defined(GL_VERTEX_ARRAY_STRIDE)
        case GL_VERTEX_ARRAY_STRIDE:
#endif // defined(GL_VERTEX_ARRAY_STRIDE)
#if defined(GL_VERTEX_ARRAY_TYPE)
        case GL_VERTEX_ARRAY_TYPE:
#endif // defined(GL_VERTEX_ARRAY_TYPE)
#if defined(GL_WEIGHT_ARRAY_BUFFER_BINDING_OES)
        case GL_WEIGHT_ARRAY_BUFFER_BINDING_OES:
#endif // defined(GL_WEIGHT_ARRAY_BUFFER_BINDING_OES)
#if defined(GL_WEIGHT_ARRAY_SIZE_OES)
        case GL_WEIGHT_ARRAY_SIZE_OES:
#endif // defined(GL_WEIGHT_ARRAY_SIZE_OES)
#if defined(GL_WEIGHT_ARRAY_STRIDE_OES)
        case GL_WEIGHT_ARRAY_STRIDE_OES:
#endif // defined(GL_WEIGHT_ARRAY_STRIDE_OES)
#if defined(GL_WEIGHT_ARRAY_TYPE_OES)
        case GL_WEIGHT_ARRAY_TYPE_OES:
#endif // defined(GL_WEIGHT_ARRAY_TYPE_OES)
            _needed = 1;
            break;
#if defined(GL_ALIASED_POINT_SIZE_RANGE)
        case GL_ALIASED_POINT_SIZE_RANGE:
#endif // defined(GL_ALIASED_POINT_SIZE_RANGE)
#if defined(GL_ALIASED_LINE_WIDTH_RANGE)
        case GL_ALIASED_LINE_WIDTH_RANGE:
#endif // defined(GL_ALIASED_LINE_WIDTH_RANGE)
#if defined(GL_DEPTH_RANGE)
        case GL_DEPTH_RANGE:
#endif // defined(GL_DEPTH_RANGE)
#if defined(GL_MAX_VIEWPORT_DIMS)
        case GL_MAX_VIEWPORT_DIMS:
#endif // defined(GL_MAX_VIEWPORT_DIMS)
#if defined(GL_SMOOTH_LINE_WIDTH_RANGE)
        case GL_SMOOTH_LINE_WIDTH_RANGE:
#endif // defined(GL_SMOOTH_LINE_WIDTH_RANGE)
#if defined(GL_SMOOTH_POINT_SIZE_RANGE)
        case GL_SMOOTH_POINT_SIZE_RANGE:
#endif // defined(GL_SMOOTH_POINT_SIZE_RANGE)
            _needed = 2;
            break;
#if defined(GL_COLOR_CLEAR_VALUE)
        case GL_COLOR_CLEAR_VALUE:
#endif // defined(GL_COLOR_CLEAR_VALUE)
#if defined(GL_COLOR_WRITEMASK)
        case GL_COLOR_WRITEMASK:
#endif // defined(GL_COLOR_WRITEMASK)
#if defined(GL_FOG_COLOR)
        case GL_FOG_COLOR:
#endif // defined(GL_FOG_COLOR)
#if defined(GL_LIGHT_MODEL_AMBIENT)
        case GL_LIGHT_MODEL_AMBIENT:
#endif // defined(GL_LIGHT_MODEL_AMBIENT)
#if defined(GL_SCISSOR_BOX)
        case GL_SCISSOR_BOX:
#endif // defined(GL_SCISSOR_BOX)
#if defined(GL_VIEWPORT)
        case GL_VIEWPORT:
#endif // defined(GL_VIEWPORT)
            _needed = 4;
            break;
#if defined(GL_MODELVIEW_MATRIX)
        case GL_MODELVIEW_MATRIX:
#endif // defined(GL_MODELVIEW_MATRIX)
#if defined(GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES)
        case GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES:
#endif // defined(GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES)
#if defined(GL_PROJECTION_MATRIX)
        case GL_PROJECTION_MATRIX:
#endif // defined(GL_PROJECTION_MATRIX)
#if defined(GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES)
        case GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES:
#endif // defined(GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES)
#if defined(GL_TEXTURE_MATRIX)
        case GL_TEXTURE_MATRIX:
#endif // defined(GL_TEXTURE_MATRIX)
#if defined(GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES)
        case GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES:
#endif // defined(GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES)
            _needed = 16;
            break;
#if defined(GL_COMPRESSED_TEXTURE_FORMATS)
        case GL_COMPRESSED_TEXTURE_FORMATS:
#endif // defined(GL_COMPRESSED_TEXTURE_FORMATS)
            _needed = getNumCompressedTextureFormats();
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glGetIntegerv(
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

#include <string.h>

/* const GLubyte * glGetString ( GLenum name ) */
static
jstring
android_glGetString
  (JNIEnv *_env, jobject _this, jint name) {
    const char * chars = (const char *)glGetString((GLenum)name);
    jstring output = _env->NewStringUTF(chars);
    return output;
}
/* void glHint ( GLenum target, GLenum mode ) */
static void
android_glHint__II
  (JNIEnv *_env, jobject _this, jint target, jint mode) {
    glHint(
        (GLenum)target,
        (GLenum)mode
    );
}

/* void glLightModelf ( GLenum pname, GLfloat param ) */
static void
android_glLightModelf__IF
  (JNIEnv *_env, jobject _this, jint pname, jfloat param) {
    glLightModelf(
        (GLenum)pname,
        (GLfloat)param
    );
}

/* void glLightModelfv ( GLenum pname, const GLfloat *params ) */
static void
android_glLightModelfv__I_3FI
  (JNIEnv *_env, jobject _this, jint pname, jfloatArray params_ref, jint offset) {
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_LIGHT_MODEL_TWO_SIDE)
        case GL_LIGHT_MODEL_TWO_SIDE:
#endif // defined(GL_LIGHT_MODEL_TWO_SIDE)
            _needed = 1;
            break;
#if defined(GL_LIGHT_MODEL_AMBIENT)
        case GL_LIGHT_MODEL_AMBIENT:
#endif // defined(GL_LIGHT_MODEL_AMBIENT)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glLightModelfv(
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glLightModelfv ( GLenum pname, const GLfloat *params ) */
static void
android_glLightModelfv__ILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_LIGHT_MODEL_TWO_SIDE)
        case GL_LIGHT_MODEL_TWO_SIDE:
#endif // defined(GL_LIGHT_MODEL_TWO_SIDE)
            _needed = 1;
            break;
#if defined(GL_LIGHT_MODEL_AMBIENT)
        case GL_LIGHT_MODEL_AMBIENT:
#endif // defined(GL_LIGHT_MODEL_AMBIENT)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glLightModelfv(
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glLightModelx ( GLenum pname, GLfixed param ) */
static void
android_glLightModelx__II
  (JNIEnv *_env, jobject _this, jint pname, jint param) {
    glLightModelx(
        (GLenum)pname,
        (GLfixed)param
    );
}

/* void glLightModelxv ( GLenum pname, const GLfixed *params ) */
static void
android_glLightModelxv__I_3II
  (JNIEnv *_env, jobject _this, jint pname, jintArray params_ref, jint offset) {
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_LIGHT_MODEL_TWO_SIDE)
        case GL_LIGHT_MODEL_TWO_SIDE:
#endif // defined(GL_LIGHT_MODEL_TWO_SIDE)
            _needed = 1;
            break;
#if defined(GL_LIGHT_MODEL_AMBIENT)
        case GL_LIGHT_MODEL_AMBIENT:
#endif // defined(GL_LIGHT_MODEL_AMBIENT)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glLightModelxv(
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glLightModelxv ( GLenum pname, const GLfixed *params ) */
static void
android_glLightModelxv__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_LIGHT_MODEL_TWO_SIDE)
        case GL_LIGHT_MODEL_TWO_SIDE:
#endif // defined(GL_LIGHT_MODEL_TWO_SIDE)
            _needed = 1;
            break;
#if defined(GL_LIGHT_MODEL_AMBIENT)
        case GL_LIGHT_MODEL_AMBIENT:
#endif // defined(GL_LIGHT_MODEL_AMBIENT)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glLightModelxv(
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glLightf ( GLenum light, GLenum pname, GLfloat param ) */
static void
android_glLightf__IIF
  (JNIEnv *_env, jobject _this, jint light, jint pname, jfloat param) {
    glLightf(
        (GLenum)light,
        (GLenum)pname,
        (GLfloat)param
    );
}

/* void glLightfv ( GLenum light, GLenum pname, const GLfloat *params ) */
static void
android_glLightfv__II_3FI
  (JNIEnv *_env, jobject _this, jint light, jint pname, jfloatArray params_ref, jint offset) {
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glLightfv(
        (GLenum)light,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glLightfv ( GLenum light, GLenum pname, const GLfloat *params ) */
static void
android_glLightfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint light, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glLightfv(
        (GLenum)light,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glLightx ( GLenum light, GLenum pname, GLfixed param ) */
static void
android_glLightx__III
  (JNIEnv *_env, jobject _this, jint light, jint pname, jint param) {
    glLightx(
        (GLenum)light,
        (GLenum)pname,
        (GLfixed)param
    );
}

/* void glLightxv ( GLenum light, GLenum pname, const GLfixed *params ) */
static void
android_glLightxv__II_3II
  (JNIEnv *_env, jobject _this, jint light, jint pname, jintArray params_ref, jint offset) {
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glLightxv(
        (GLenum)light,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glLightxv ( GLenum light, GLenum pname, const GLfixed *params ) */
static void
android_glLightxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint light, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glLightxv(
        (GLenum)light,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glLineWidth ( GLfloat width ) */
static void
android_glLineWidth__F
  (JNIEnv *_env, jobject _this, jfloat width) {
    glLineWidth(
        (GLfloat)width
    );
}

/* void glLineWidthx ( GLfixed width ) */
static void
android_glLineWidthx__I
  (JNIEnv *_env, jobject _this, jint width) {
    glLineWidthx(
        (GLfixed)width
    );
}

/* void glLoadIdentity ( void ) */
static void
android_glLoadIdentity__
  (JNIEnv *_env, jobject _this) {
    glLoadIdentity();
}

/* void glLoadMatrixf ( const GLfloat *m ) */
static void
android_glLoadMatrixf___3FI
  (JNIEnv *_env, jobject _this, jfloatArray m_ref, jint offset) {
    GLfloat *m_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *m = (GLfloat *) 0;

    if (!m_ref) {
        _env->ThrowNew(IAEClass, "m == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(m_ref) - offset;
    m_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(m_ref, (jboolean *)0);
    m = m_base + offset;

    glLoadMatrixf(
        (GLfloat *)m
    );

exit:
    if (m_base) {
        _env->ReleasePrimitiveArrayCritical(m_ref, m_base,
            JNI_ABORT);
    }
}

/* void glLoadMatrixf ( const GLfloat *m ) */
static void
android_glLoadMatrixf__Ljava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jobject m_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *m = (GLfloat *) 0;

    m = (GLfloat *)getPointer(_env, m_buf, &_array, &_remaining);
    glLoadMatrixf(
        (GLfloat *)m
    );
    if (_array) {
        releasePointer(_env, _array, m, JNI_FALSE);
    }
}

/* void glLoadMatrixx ( const GLfixed *m ) */
static void
android_glLoadMatrixx___3II
  (JNIEnv *_env, jobject _this, jintArray m_ref, jint offset) {
    GLfixed *m_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *m = (GLfixed *) 0;

    if (!m_ref) {
        _env->ThrowNew(IAEClass, "m == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(m_ref) - offset;
    m_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(m_ref, (jboolean *)0);
    m = m_base + offset;

    glLoadMatrixx(
        (GLfixed *)m
    );

exit:
    if (m_base) {
        _env->ReleasePrimitiveArrayCritical(m_ref, m_base,
            JNI_ABORT);
    }
}

/* void glLoadMatrixx ( const GLfixed *m ) */
static void
android_glLoadMatrixx__Ljava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jobject m_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *m = (GLfixed *) 0;

    m = (GLfixed *)getPointer(_env, m_buf, &_array, &_remaining);
    glLoadMatrixx(
        (GLfixed *)m
    );
    if (_array) {
        releasePointer(_env, _array, m, JNI_FALSE);
    }
}

/* void glLogicOp ( GLenum opcode ) */
static void
android_glLogicOp__I
  (JNIEnv *_env, jobject _this, jint opcode) {
    glLogicOp(
        (GLenum)opcode
    );
}

/* void glMaterialf ( GLenum face, GLenum pname, GLfloat param ) */
static void
android_glMaterialf__IIF
  (JNIEnv *_env, jobject _this, jint face, jint pname, jfloat param) {
    glMaterialf(
        (GLenum)face,
        (GLenum)pname,
        (GLfloat)param
    );
}

/* void glMaterialfv ( GLenum face, GLenum pname, const GLfloat *params ) */
static void
android_glMaterialfv__II_3FI
  (JNIEnv *_env, jobject _this, jint face, jint pname, jfloatArray params_ref, jint offset) {
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glMaterialfv(
        (GLenum)face,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glMaterialfv ( GLenum face, GLenum pname, const GLfloat *params ) */
static void
android_glMaterialfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint face, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glMaterialfv(
        (GLenum)face,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glMaterialx ( GLenum face, GLenum pname, GLfixed param ) */
static void
android_glMaterialx__III
  (JNIEnv *_env, jobject _this, jint face, jint pname, jint param) {
    glMaterialx(
        (GLenum)face,
        (GLenum)pname,
        (GLfixed)param
    );
}

/* void glMaterialxv ( GLenum face, GLenum pname, const GLfixed *params ) */
static void
android_glMaterialxv__II_3II
  (JNIEnv *_env, jobject _this, jint face, jint pname, jintArray params_ref, jint offset) {
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glMaterialxv(
        (GLenum)face,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glMaterialxv ( GLenum face, GLenum pname, const GLfixed *params ) */
static void
android_glMaterialxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint face, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glMaterialxv(
        (GLenum)face,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glMatrixMode ( GLenum mode ) */
static void
android_glMatrixMode__I
  (JNIEnv *_env, jobject _this, jint mode) {
    glMatrixMode(
        (GLenum)mode
    );
}

/* void glMultMatrixf ( const GLfloat *m ) */
static void
android_glMultMatrixf___3FI
  (JNIEnv *_env, jobject _this, jfloatArray m_ref, jint offset) {
    GLfloat *m_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *m = (GLfloat *) 0;

    if (!m_ref) {
        _env->ThrowNew(IAEClass, "m == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(m_ref) - offset;
    m_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(m_ref, (jboolean *)0);
    m = m_base + offset;

    glMultMatrixf(
        (GLfloat *)m
    );

exit:
    if (m_base) {
        _env->ReleasePrimitiveArrayCritical(m_ref, m_base,
            JNI_ABORT);
    }
}

/* void glMultMatrixf ( const GLfloat *m ) */
static void
android_glMultMatrixf__Ljava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jobject m_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *m = (GLfloat *) 0;

    m = (GLfloat *)getPointer(_env, m_buf, &_array, &_remaining);
    glMultMatrixf(
        (GLfloat *)m
    );
    if (_array) {
        releasePointer(_env, _array, m, JNI_FALSE);
    }
}

/* void glMultMatrixx ( const GLfixed *m ) */
static void
android_glMultMatrixx___3II
  (JNIEnv *_env, jobject _this, jintArray m_ref, jint offset) {
    GLfixed *m_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *m = (GLfixed *) 0;

    if (!m_ref) {
        _env->ThrowNew(IAEClass, "m == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(m_ref) - offset;
    m_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(m_ref, (jboolean *)0);
    m = m_base + offset;

    glMultMatrixx(
        (GLfixed *)m
    );

exit:
    if (m_base) {
        _env->ReleasePrimitiveArrayCritical(m_ref, m_base,
            JNI_ABORT);
    }
}

/* void glMultMatrixx ( const GLfixed *m ) */
static void
android_glMultMatrixx__Ljava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jobject m_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *m = (GLfixed *) 0;

    m = (GLfixed *)getPointer(_env, m_buf, &_array, &_remaining);
    glMultMatrixx(
        (GLfixed *)m
    );
    if (_array) {
        releasePointer(_env, _array, m, JNI_FALSE);
    }
}

/* void glMultiTexCoord4f ( GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q ) */
static void
android_glMultiTexCoord4f__IFFFF
  (JNIEnv *_env, jobject _this, jint target, jfloat s, jfloat t, jfloat r, jfloat q) {
    glMultiTexCoord4f(
        (GLenum)target,
        (GLfloat)s,
        (GLfloat)t,
        (GLfloat)r,
        (GLfloat)q
    );
}

/* void glMultiTexCoord4x ( GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q ) */
static void
android_glMultiTexCoord4x__IIIII
  (JNIEnv *_env, jobject _this, jint target, jint s, jint t, jint r, jint q) {
    glMultiTexCoord4x(
        (GLenum)target,
        (GLfixed)s,
        (GLfixed)t,
        (GLfixed)r,
        (GLfixed)q
    );
}

/* void glNormal3f ( GLfloat nx, GLfloat ny, GLfloat nz ) */
static void
android_glNormal3f__FFF
  (JNIEnv *_env, jobject _this, jfloat nx, jfloat ny, jfloat nz) {
    glNormal3f(
        (GLfloat)nx,
        (GLfloat)ny,
        (GLfloat)nz
    );
}

/* void glNormal3x ( GLfixed nx, GLfixed ny, GLfixed nz ) */
static void
android_glNormal3x__III
  (JNIEnv *_env, jobject _this, jint nx, jint ny, jint nz) {
    glNormal3x(
        (GLfixed)nx,
        (GLfixed)ny,
        (GLfixed)nz
    );
}

/* void glNormalPointer ( GLenum type, GLsizei stride, const GLvoid *pointer ) */
static void
android_glNormalPointerBounds__IILjava_nio_Buffer_2I
  (JNIEnv *_env, jobject _this, jint type, jint stride, jobject pointer_buf, jint remaining) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pointer = (GLvoid *) 0;

    if (pointer_buf) {
        pointer = (GLvoid *) getDirectBufferPointer(_env, pointer_buf);
        if ( ! pointer ) {
            return;
        }
    }
    glNormalPointerBounds(
        (GLenum)type,
        (GLsizei)stride,
        (GLvoid *)pointer,
        (GLsizei)remaining
    );
}

/* void glOrthof ( GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar ) */
static void
android_glOrthof__FFFFFF
  (JNIEnv *_env, jobject _this, jfloat left, jfloat right, jfloat bottom, jfloat top, jfloat zNear, jfloat zFar) {
    glOrthof(
        (GLfloat)left,
        (GLfloat)right,
        (GLfloat)bottom,
        (GLfloat)top,
        (GLfloat)zNear,
        (GLfloat)zFar
    );
}

/* void glOrthox ( GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar ) */
static void
android_glOrthox__IIIIII
  (JNIEnv *_env, jobject _this, jint left, jint right, jint bottom, jint top, jint zNear, jint zFar) {
    glOrthox(
        (GLfixed)left,
        (GLfixed)right,
        (GLfixed)bottom,
        (GLfixed)top,
        (GLfixed)zNear,
        (GLfixed)zFar
    );
}

/* void glPixelStorei ( GLenum pname, GLint param ) */
static void
android_glPixelStorei__II
  (JNIEnv *_env, jobject _this, jint pname, jint param) {
    glPixelStorei(
        (GLenum)pname,
        (GLint)param
    );
}

/* void glPointSize ( GLfloat size ) */
static void
android_glPointSize__F
  (JNIEnv *_env, jobject _this, jfloat size) {
    glPointSize(
        (GLfloat)size
    );
}

/* void glPointSizex ( GLfixed size ) */
static void
android_glPointSizex__I
  (JNIEnv *_env, jobject _this, jint size) {
    glPointSizex(
        (GLfixed)size
    );
}

/* void glPolygonOffset ( GLfloat factor, GLfloat units ) */
static void
android_glPolygonOffset__FF
  (JNIEnv *_env, jobject _this, jfloat factor, jfloat units) {
    glPolygonOffset(
        (GLfloat)factor,
        (GLfloat)units
    );
}

/* void glPolygonOffsetx ( GLfixed factor, GLfixed units ) */
static void
android_glPolygonOffsetx__II
  (JNIEnv *_env, jobject _this, jint factor, jint units) {
    glPolygonOffsetx(
        (GLfixed)factor,
        (GLfixed)units
    );
}

/* void glPopMatrix ( void ) */
static void
android_glPopMatrix__
  (JNIEnv *_env, jobject _this) {
    glPopMatrix();
}

/* void glPushMatrix ( void ) */
static void
android_glPushMatrix__
  (JNIEnv *_env, jobject _this) {
    glPushMatrix();
}

/* void glReadPixels ( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels ) */
static void
android_glReadPixels__IIIIIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint x, jint y, jint width, jint height, jint format, jint type, jobject pixels_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pixels = (GLvoid *) 0;

    pixels = (GLvoid *)getPointer(_env, pixels_buf, &_array, &_remaining);
    glReadPixels(
        (GLint)x,
        (GLint)y,
        (GLsizei)width,
        (GLsizei)height,
        (GLenum)format,
        (GLenum)type,
        (GLvoid *)pixels
    );
    if (_array) {
        releasePointer(_env, _array, pixels, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glRotatef ( GLfloat angle, GLfloat x, GLfloat y, GLfloat z ) */
static void
android_glRotatef__FFFF
  (JNIEnv *_env, jobject _this, jfloat angle, jfloat x, jfloat y, jfloat z) {
    glRotatef(
        (GLfloat)angle,
        (GLfloat)x,
        (GLfloat)y,
        (GLfloat)z
    );
}

/* void glRotatex ( GLfixed angle, GLfixed x, GLfixed y, GLfixed z ) */
static void
android_glRotatex__IIII
  (JNIEnv *_env, jobject _this, jint angle, jint x, jint y, jint z) {
    glRotatex(
        (GLfixed)angle,
        (GLfixed)x,
        (GLfixed)y,
        (GLfixed)z
    );
}

/* void glSampleCoverage ( GLclampf value, GLboolean invert ) */
static void
android_glSampleCoverage__FZ
  (JNIEnv *_env, jobject _this, jfloat value, jboolean invert) {
    glSampleCoverage(
        (GLclampf)value,
        (GLboolean)invert
    );
}

/* void glSampleCoveragex ( GLclampx value, GLboolean invert ) */
static void
android_glSampleCoveragex__IZ
  (JNIEnv *_env, jobject _this, jint value, jboolean invert) {
    glSampleCoveragex(
        (GLclampx)value,
        (GLboolean)invert
    );
}

/* void glScalef ( GLfloat x, GLfloat y, GLfloat z ) */
static void
android_glScalef__FFF
  (JNIEnv *_env, jobject _this, jfloat x, jfloat y, jfloat z) {
    glScalef(
        (GLfloat)x,
        (GLfloat)y,
        (GLfloat)z
    );
}

/* void glScalex ( GLfixed x, GLfixed y, GLfixed z ) */
static void
android_glScalex__III
  (JNIEnv *_env, jobject _this, jint x, jint y, jint z) {
    glScalex(
        (GLfixed)x,
        (GLfixed)y,
        (GLfixed)z
    );
}

/* void glScissor ( GLint x, GLint y, GLsizei width, GLsizei height ) */
static void
android_glScissor__IIII
  (JNIEnv *_env, jobject _this, jint x, jint y, jint width, jint height) {
    glScissor(
        (GLint)x,
        (GLint)y,
        (GLsizei)width,
        (GLsizei)height
    );
}

/* void glShadeModel ( GLenum mode ) */
static void
android_glShadeModel__I
  (JNIEnv *_env, jobject _this, jint mode) {
    glShadeModel(
        (GLenum)mode
    );
}

/* void glStencilFunc ( GLenum func, GLint ref, GLuint mask ) */
static void
android_glStencilFunc__III
  (JNIEnv *_env, jobject _this, jint func, jint ref, jint mask) {
    glStencilFunc(
        (GLenum)func,
        (GLint)ref,
        (GLuint)mask
    );
}

/* void glStencilMask ( GLuint mask ) */
static void
android_glStencilMask__I
  (JNIEnv *_env, jobject _this, jint mask) {
    glStencilMask(
        (GLuint)mask
    );
}

/* void glStencilOp ( GLenum fail, GLenum zfail, GLenum zpass ) */
static void
android_glStencilOp__III
  (JNIEnv *_env, jobject _this, jint fail, jint zfail, jint zpass) {
    glStencilOp(
        (GLenum)fail,
        (GLenum)zfail,
        (GLenum)zpass
    );
}

/* void glTexCoordPointer ( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer ) */
static void
android_glTexCoordPointerBounds__IIILjava_nio_Buffer_2I
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jobject pointer_buf, jint remaining) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pointer = (GLvoid *) 0;

    if (pointer_buf) {
        pointer = (GLvoid *) getDirectBufferPointer(_env, pointer_buf);
        if ( ! pointer ) {
            return;
        }
    }
    glTexCoordPointerBounds(
        (GLint)size,
        (GLenum)type,
        (GLsizei)stride,
        (GLvoid *)pointer,
        (GLsizei)remaining
    );
}

/* void glTexEnvf ( GLenum target, GLenum pname, GLfloat param ) */
static void
android_glTexEnvf__IIF
  (JNIEnv *_env, jobject _this, jint target, jint pname, jfloat param) {
    glTexEnvf(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat)param
    );
}

/* void glTexEnvfv ( GLenum target, GLenum pname, const GLfloat *params ) */
static void
android_glTexEnvfv__II_3FI
  (JNIEnv *_env, jobject _this, jint target, jint pname, jfloatArray params_ref, jint offset) {
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glTexEnvfv(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glTexEnvfv ( GLenum target, GLenum pname, const GLfloat *params ) */
static void
android_glTexEnvfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glTexEnvfv(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glTexEnvx ( GLenum target, GLenum pname, GLfixed param ) */
static void
android_glTexEnvx__III
  (JNIEnv *_env, jobject _this, jint target, jint pname, jint param) {
    glTexEnvx(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed)param
    );
}

/* void glTexEnvxv ( GLenum target, GLenum pname, const GLfixed *params ) */
static void
android_glTexEnvxv__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glTexEnvxv(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glTexEnvxv ( GLenum target, GLenum pname, const GLfixed *params ) */
static void
android_glTexEnvxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glTexEnvxv(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glTexImage2D ( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels ) */
static void
android_glTexImage2D__IIIIIIIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint target, jint level, jint internalformat, jint width, jint height, jint border, jint format, jint type, jobject pixels_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pixels = (GLvoid *) 0;

    if (pixels_buf) {
        pixels = (GLvoid *)getPointer(_env, pixels_buf, &_array, &_remaining);
    }
    glTexImage2D(
        (GLenum)target,
        (GLint)level,
        (GLint)internalformat,
        (GLsizei)width,
        (GLsizei)height,
        (GLint)border,
        (GLenum)format,
        (GLenum)type,
        (GLvoid *)pixels
    );
    if (_array) {
        releasePointer(_env, _array, pixels, JNI_FALSE);
    }
}

/* void glTexParameterf ( GLenum target, GLenum pname, GLfloat param ) */
static void
android_glTexParameterf__IIF
  (JNIEnv *_env, jobject _this, jint target, jint pname, jfloat param) {
    glTexParameterf(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat)param
    );
}

/* void glTexParameterx ( GLenum target, GLenum pname, GLfixed param ) */
static void
android_glTexParameterx__III
  (JNIEnv *_env, jobject _this, jint target, jint pname, jint param) {
    glTexParameterx(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed)param
    );
}

/* void glTexSubImage2D ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels ) */
static void
android_glTexSubImage2D__IIIIIIIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint target, jint level, jint xoffset, jint yoffset, jint width, jint height, jint format, jint type, jobject pixels_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pixels = (GLvoid *) 0;

    if (pixels_buf) {
        pixels = (GLvoid *)getPointer(_env, pixels_buf, &_array, &_remaining);
    }
    glTexSubImage2D(
        (GLenum)target,
        (GLint)level,
        (GLint)xoffset,
        (GLint)yoffset,
        (GLsizei)width,
        (GLsizei)height,
        (GLenum)format,
        (GLenum)type,
        (GLvoid *)pixels
    );
    if (_array) {
        releasePointer(_env, _array, pixels, JNI_FALSE);
    }
}

/* void glTranslatef ( GLfloat x, GLfloat y, GLfloat z ) */
static void
android_glTranslatef__FFF
  (JNIEnv *_env, jobject _this, jfloat x, jfloat y, jfloat z) {
    glTranslatef(
        (GLfloat)x,
        (GLfloat)y,
        (GLfloat)z
    );
}

/* void glTranslatex ( GLfixed x, GLfixed y, GLfixed z ) */
static void
android_glTranslatex__III
  (JNIEnv *_env, jobject _this, jint x, jint y, jint z) {
    glTranslatex(
        (GLfixed)x,
        (GLfixed)y,
        (GLfixed)z
    );
}

/* void glVertexPointer ( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer ) */
static void
android_glVertexPointerBounds__IIILjava_nio_Buffer_2I
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jobject pointer_buf, jint remaining) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pointer = (GLvoid *) 0;

    if (pointer_buf) {
        pointer = (GLvoid *) getDirectBufferPointer(_env, pointer_buf);
        if ( ! pointer ) {
            return;
        }
    }
    glVertexPointerBounds(
        (GLint)size,
        (GLenum)type,
        (GLsizei)stride,
        (GLvoid *)pointer,
        (GLsizei)remaining
    );
}

/* void glViewport ( GLint x, GLint y, GLsizei width, GLsizei height ) */
static void
android_glViewport__IIII
  (JNIEnv *_env, jobject _this, jint x, jint y, jint width, jint height) {
    glViewport(
        (GLint)x,
        (GLint)y,
        (GLsizei)width,
        (GLsizei)height
    );
}

/* GLbitfield glQueryMatrixxOES ( GLfixed *mantissa, GLint *exponent ) */
static jint
android_glQueryMatrixxOES___3II_3II
  (JNIEnv *_env, jobject _this, jintArray mantissa_ref, jint mantissaOffset, jintArray exponent_ref, jint exponentOffset) {
    jint _exception = 0;
    GLbitfield _returnValue = -1;
    GLfixed *mantissa_base = (GLfixed *) 0;
    jint _mantissaRemaining;
    GLfixed *mantissa = (GLfixed *) 0;
    GLint *exponent_base = (GLint *) 0;
    jint _exponentRemaining;
    GLint *exponent = (GLint *) 0;

    if (!mantissa_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "mantissa == null");
        goto exit;
    }
    if (mantissaOffset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "mantissaOffset < 0");
        goto exit;
    }
    _mantissaRemaining = _env->GetArrayLength(mantissa_ref) - mantissaOffset;
    if (_mantissaRemaining < 16) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - mantissaOffset < 16");
        goto exit;
    }
    mantissa_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(mantissa_ref, (jboolean *)0);
    mantissa = mantissa_base + mantissaOffset;

    if (!exponent_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "exponent == null");
        goto exit;
    }
    if (exponentOffset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "exponentOffset < 0");
        goto exit;
    }
    _exponentRemaining = _env->GetArrayLength(exponent_ref) - exponentOffset;
    if (_exponentRemaining < 16) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - exponentOffset < 16");
        goto exit;
    }
    exponent_base = (GLint *)
        _env->GetPrimitiveArrayCritical(exponent_ref, (jboolean *)0);
    exponent = exponent_base + exponentOffset;

    _returnValue = glQueryMatrixxOES(
        (GLfixed *)mantissa,
        (GLint *)exponent
    );

exit:
    if (exponent_base) {
        _env->ReleasePrimitiveArrayCritical(exponent_ref, exponent_base,
            _exception ? JNI_ABORT: 0);
    }
    if (mantissa_base) {
        _env->ReleasePrimitiveArrayCritical(mantissa_ref, mantissa_base,
            _exception ? JNI_ABORT: 0);
    }
    return _returnValue;
}

/* GLbitfield glQueryMatrixxOES ( GLfixed *mantissa, GLint *exponent ) */
static jint
android_glQueryMatrixxOES__Ljava_nio_IntBuffer_2Ljava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jobject mantissa_buf, jobject exponent_buf) {
    jint _exception = 0;
    jarray _mantissaArray = (jarray) 0;
    jarray _exponentArray = (jarray) 0;
    GLbitfield _returnValue = -1;
    jint _mantissaRemaining;
    GLfixed *mantissa = (GLfixed *) 0;
    jint _exponentRemaining;
    GLint *exponent = (GLint *) 0;

    mantissa = (GLfixed *)getPointer(_env, mantissa_buf, &_mantissaArray, &_mantissaRemaining);
    if (_mantissaRemaining < 16) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < 16");
        goto exit;
    }
    exponent = (GLint *)getPointer(_env, exponent_buf, &_exponentArray, &_exponentRemaining);
    if (_exponentRemaining < 16) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < 16");
        goto exit;
    }
    _returnValue = glQueryMatrixxOES(
        (GLfixed *)mantissa,
        (GLint *)exponent
    );

exit:
    if (_mantissaArray) {
        releasePointer(_env, _mantissaArray, exponent, _exception ? JNI_FALSE : JNI_TRUE);
    }
    if (_exponentArray) {
        releasePointer(_env, _exponentArray, mantissa, _exception ? JNI_FALSE : JNI_TRUE);
    }
    return _returnValue;
}

/* void glBindBuffer ( GLenum target, GLuint buffer ) */
static void
android_glBindBuffer__II
  (JNIEnv *_env, jobject _this, jint target, jint buffer) {
    glBindBuffer(
        (GLenum)target,
        (GLuint)buffer
    );
}

/* void glBufferData ( GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage ) */
static void
android_glBufferData__IILjava_nio_Buffer_2I
  (JNIEnv *_env, jobject _this, jint target, jint size, jobject data_buf, jint usage) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *data = (GLvoid *) 0;

    if (data_buf) {
        data = (GLvoid *)getPointer(_env, data_buf, &_array, &_remaining);
    }
    glBufferData(
        (GLenum)target,
        (GLsizeiptr)size,
        (GLvoid *)data,
        (GLenum)usage
    );
    if (_array) {
        releasePointer(_env, _array, data, JNI_FALSE);
    }
}

/* void glBufferSubData ( GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data ) */
static void
android_glBufferSubData__IIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint target, jint offset, jint size, jobject data_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *data = (GLvoid *) 0;

    data = (GLvoid *)getPointer(_env, data_buf, &_array, &_remaining);
    glBufferSubData(
        (GLenum)target,
        (GLintptr)offset,
        (GLsizeiptr)size,
        (GLvoid *)data
    );
    if (_array) {
        releasePointer(_env, _array, data, JNI_FALSE);
    }
}

/* void glClipPlanef ( GLenum plane, const GLfloat *equation ) */
static void
android_glClipPlanef__I_3FI
  (JNIEnv *_env, jobject _this, jint plane, jfloatArray equation_ref, jint offset) {
    GLfloat *equation_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *equation = (GLfloat *) 0;

    if (!equation_ref) {
        _env->ThrowNew(IAEClass, "equation == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(equation_ref) - offset;
    if (_remaining < 4) {
        _env->ThrowNew(IAEClass, "length - offset < 4");
        goto exit;
    }
    equation_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(equation_ref, (jboolean *)0);
    equation = equation_base + offset;

    glClipPlanef(
        (GLenum)plane,
        (GLfloat *)equation
    );

exit:
    if (equation_base) {
        _env->ReleasePrimitiveArrayCritical(equation_ref, equation_base,
            JNI_ABORT);
    }
}

/* void glClipPlanef ( GLenum plane, const GLfloat *equation ) */
static void
android_glClipPlanef__ILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint plane, jobject equation_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *equation = (GLfloat *) 0;

    equation = (GLfloat *)getPointer(_env, equation_buf, &_array, &_remaining);
    if (_remaining < 4) {
        _env->ThrowNew(IAEClass, "remaining() < 4");
        goto exit;
    }
    glClipPlanef(
        (GLenum)plane,
        (GLfloat *)equation
    );

exit:
    if (_array) {
        releasePointer(_env, _array, equation, JNI_FALSE);
    }
}

/* void glClipPlanex ( GLenum plane, const GLfixed *equation ) */
static void
android_glClipPlanex__I_3II
  (JNIEnv *_env, jobject _this, jint plane, jintArray equation_ref, jint offset) {
    GLfixed *equation_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *equation = (GLfixed *) 0;

    if (!equation_ref) {
        _env->ThrowNew(IAEClass, "equation == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(equation_ref) - offset;
    if (_remaining < 4) {
        _env->ThrowNew(IAEClass, "length - offset < 4");
        goto exit;
    }
    equation_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(equation_ref, (jboolean *)0);
    equation = equation_base + offset;

    glClipPlanex(
        (GLenum)plane,
        (GLfixed *)equation
    );

exit:
    if (equation_base) {
        _env->ReleasePrimitiveArrayCritical(equation_ref, equation_base,
            JNI_ABORT);
    }
}

/* void glClipPlanex ( GLenum plane, const GLfixed *equation ) */
static void
android_glClipPlanex__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint plane, jobject equation_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *equation = (GLfixed *) 0;

    equation = (GLfixed *)getPointer(_env, equation_buf, &_array, &_remaining);
    if (_remaining < 4) {
        _env->ThrowNew(IAEClass, "remaining() < 4");
        goto exit;
    }
    glClipPlanex(
        (GLenum)plane,
        (GLfixed *)equation
    );

exit:
    if (_array) {
        releasePointer(_env, _array, equation, JNI_FALSE);
    }
}

/* void glColor4ub ( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha ) */
static void
android_glColor4ub__BBBB
  (JNIEnv *_env, jobject _this, jbyte red, jbyte green, jbyte blue, jbyte alpha) {
    glColor4ub(
        (GLubyte)red,
        (GLubyte)green,
        (GLubyte)blue,
        (GLubyte)alpha
    );
}

/* void glColorPointer ( GLint size, GLenum type, GLsizei stride, GLint offset ) */
static void
android_glColorPointer__IIII
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jint offset) {
    glColorPointer(
        (GLint)size,
        (GLenum)type,
        (GLsizei)stride,
        (const GLvoid *)offset
    );
}

/* void glDeleteBuffers ( GLsizei n, const GLuint *buffers ) */
static void
android_glDeleteBuffers__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray buffers_ref, jint offset) {
    GLuint *buffers_base = (GLuint *) 0;
    jint _remaining;
    GLuint *buffers = (GLuint *) 0;

    if (!buffers_ref) {
        _env->ThrowNew(IAEClass, "buffers == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(buffers_ref) - offset;
    if (_remaining < n) {
        _env->ThrowNew(IAEClass, "length - offset < n");
        goto exit;
    }
    buffers_base = (GLuint *)
        _env->GetPrimitiveArrayCritical(buffers_ref, (jboolean *)0);
    buffers = buffers_base + offset;

    glDeleteBuffers(
        (GLsizei)n,
        (GLuint *)buffers
    );

exit:
    if (buffers_base) {
        _env->ReleasePrimitiveArrayCritical(buffers_ref, buffers_base,
            JNI_ABORT);
    }
}

/* void glDeleteBuffers ( GLsizei n, const GLuint *buffers ) */
static void
android_glDeleteBuffers__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject buffers_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLuint *buffers = (GLuint *) 0;

    buffers = (GLuint *)getPointer(_env, buffers_buf, &_array, &_remaining);
    if (_remaining < n) {
        _env->ThrowNew(IAEClass, "remaining() < n");
        goto exit;
    }
    glDeleteBuffers(
        (GLsizei)n,
        (GLuint *)buffers
    );

exit:
    if (_array) {
        releasePointer(_env, _array, buffers, JNI_FALSE);
    }
}

/* void glDrawElements ( GLenum mode, GLsizei count, GLenum type, GLint offset ) */
static void
android_glDrawElements__IIII
  (JNIEnv *_env, jobject _this, jint mode, jint count, jint type, jint offset) {
    glDrawElements(
        (GLenum)mode,
        (GLsizei)count,
        (GLenum)type,
        (const GLvoid *)offset
    );
}

/* void glGenBuffers ( GLsizei n, GLuint *buffers ) */
static void
android_glGenBuffers__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray buffers_ref, jint offset) {
    jint _exception = 0;
    GLuint *buffers_base = (GLuint *) 0;
    jint _remaining;
    GLuint *buffers = (GLuint *) 0;

    if (!buffers_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "buffers == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(buffers_ref) - offset;
    if (_remaining < n) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < n");
        goto exit;
    }
    buffers_base = (GLuint *)
        _env->GetPrimitiveArrayCritical(buffers_ref, (jboolean *)0);
    buffers = buffers_base + offset;

    glGenBuffers(
        (GLsizei)n,
        (GLuint *)buffers
    );

exit:
    if (buffers_base) {
        _env->ReleasePrimitiveArrayCritical(buffers_ref, buffers_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGenBuffers ( GLsizei n, GLuint *buffers ) */
static void
android_glGenBuffers__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject buffers_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLuint *buffers = (GLuint *) 0;

    buffers = (GLuint *)getPointer(_env, buffers_buf, &_array, &_remaining);
    if (_remaining < n) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < n");
        goto exit;
    }
    glGenBuffers(
        (GLsizei)n,
        (GLuint *)buffers
    );

exit:
    if (_array) {
        releasePointer(_env, _array, buffers, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetBooleanv ( GLenum pname, GLboolean *params ) */
static void
android_glGetBooleanv__I_3ZI
  (JNIEnv *_env, jobject _this, jint pname, jbooleanArray params_ref, jint offset) {
    jint _exception = 0;
    GLboolean *params_base = (GLboolean *) 0;
    jint _remaining;
    GLboolean *params = (GLboolean *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    params_base = (GLboolean *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetBooleanv(
        (GLenum)pname,
        (GLboolean *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetBooleanv ( GLenum pname, GLboolean *params ) */
static void
android_glGetBooleanv__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLboolean *params = (GLboolean *) 0;

    params = (GLboolean *)getPointer(_env, params_buf, &_array, &_remaining);
    glGetBooleanv(
        (GLenum)pname,
        (GLboolean *)params
    );
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetBufferParameteriv ( GLenum target, GLenum pname, GLint *params ) */
static void
android_glGetBufferParameteriv__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGetBufferParameteriv");
}

/* void glGetBufferParameteriv ( GLenum target, GLenum pname, GLint *params ) */
static void
android_glGetBufferParameteriv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glGetBufferParameteriv");
}

/* void glGetClipPlanef ( GLenum pname, GLfloat *eqn ) */
static void
android_glGetClipPlanef__I_3FI
  (JNIEnv *_env, jobject _this, jint pname, jfloatArray eqn_ref, jint offset) {
    jint _exception = 0;
    GLfloat *eqn_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *eqn = (GLfloat *) 0;

    if (!eqn_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "eqn == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(eqn_ref) - offset;
    eqn_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(eqn_ref, (jboolean *)0);
    eqn = eqn_base + offset;

    glGetClipPlanef(
        (GLenum)pname,
        (GLfloat *)eqn
    );

exit:
    if (eqn_base) {
        _env->ReleasePrimitiveArrayCritical(eqn_ref, eqn_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetClipPlanef ( GLenum pname, GLfloat *eqn ) */
static void
android_glGetClipPlanef__ILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject eqn_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *eqn = (GLfloat *) 0;

    eqn = (GLfloat *)getPointer(_env, eqn_buf, &_array, &_remaining);
    glGetClipPlanef(
        (GLenum)pname,
        (GLfloat *)eqn
    );
    if (_array) {
        releasePointer(_env, _array, eqn, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetClipPlanex ( GLenum pname, GLfixed *eqn ) */
static void
android_glGetClipPlanex__I_3II
  (JNIEnv *_env, jobject _this, jint pname, jintArray eqn_ref, jint offset) {
    jint _exception = 0;
    GLfixed *eqn_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *eqn = (GLfixed *) 0;

    if (!eqn_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "eqn == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(eqn_ref) - offset;
    eqn_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(eqn_ref, (jboolean *)0);
    eqn = eqn_base + offset;

    glGetClipPlanex(
        (GLenum)pname,
        (GLfixed *)eqn
    );

exit:
    if (eqn_base) {
        _env->ReleasePrimitiveArrayCritical(eqn_ref, eqn_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetClipPlanex ( GLenum pname, GLfixed *eqn ) */
static void
android_glGetClipPlanex__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject eqn_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *eqn = (GLfixed *) 0;

    eqn = (GLfixed *)getPointer(_env, eqn_buf, &_array, &_remaining);
    glGetClipPlanex(
        (GLenum)pname,
        (GLfixed *)eqn
    );
    if (_array) {
        releasePointer(_env, _array, eqn, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetFixedv ( GLenum pname, GLfixed *params ) */
static void
android_glGetFixedv__I_3II
  (JNIEnv *_env, jobject _this, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetFixedv(
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetFixedv ( GLenum pname, GLfixed *params ) */
static void
android_glGetFixedv__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    glGetFixedv(
        (GLenum)pname,
        (GLfixed *)params
    );
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetFloatv ( GLenum pname, GLfloat *params ) */
static void
android_glGetFloatv__I_3FI
  (JNIEnv *_env, jobject _this, jint pname, jfloatArray params_ref, jint offset) {
    jint _exception = 0;
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetFloatv(
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetFloatv ( GLenum pname, GLfloat *params ) */
static void
android_glGetFloatv__ILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    glGetFloatv(
        (GLenum)pname,
        (GLfloat *)params
    );
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetLightfv ( GLenum light, GLenum pname, GLfloat *params ) */
static void
android_glGetLightfv__II_3FI
  (JNIEnv *_env, jobject _this, jint light, jint pname, jfloatArray params_ref, jint offset) {
    jint _exception = 0;
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetLightfv(
        (GLenum)light,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetLightfv ( GLenum light, GLenum pname, GLfloat *params ) */
static void
android_glGetLightfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint light, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glGetLightfv(
        (GLenum)light,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetLightxv ( GLenum light, GLenum pname, GLfixed *params ) */
static void
android_glGetLightxv__II_3II
  (JNIEnv *_env, jobject _this, jint light, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetLightxv(
        (GLenum)light,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetLightxv ( GLenum light, GLenum pname, GLfixed *params ) */
static void
android_glGetLightxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint light, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SPOT_EXPONENT)
        case GL_SPOT_EXPONENT:
#endif // defined(GL_SPOT_EXPONENT)
#if defined(GL_SPOT_CUTOFF)
        case GL_SPOT_CUTOFF:
#endif // defined(GL_SPOT_CUTOFF)
#if defined(GL_CONSTANT_ATTENUATION)
        case GL_CONSTANT_ATTENUATION:
#endif // defined(GL_CONSTANT_ATTENUATION)
#if defined(GL_LINEAR_ATTENUATION)
        case GL_LINEAR_ATTENUATION:
#endif // defined(GL_LINEAR_ATTENUATION)
#if defined(GL_QUADRATIC_ATTENUATION)
        case GL_QUADRATIC_ATTENUATION:
#endif // defined(GL_QUADRATIC_ATTENUATION)
            _needed = 1;
            break;
#if defined(GL_SPOT_DIRECTION)
        case GL_SPOT_DIRECTION:
#endif // defined(GL_SPOT_DIRECTION)
            _needed = 3;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glGetLightxv(
        (GLenum)light,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetMaterialfv ( GLenum face, GLenum pname, GLfloat *params ) */
static void
android_glGetMaterialfv__II_3FI
  (JNIEnv *_env, jobject _this, jint face, jint pname, jfloatArray params_ref, jint offset) {
    jint _exception = 0;
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetMaterialfv(
        (GLenum)face,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetMaterialfv ( GLenum face, GLenum pname, GLfloat *params ) */
static void
android_glGetMaterialfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint face, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glGetMaterialfv(
        (GLenum)face,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetMaterialxv ( GLenum face, GLenum pname, GLfixed *params ) */
static void
android_glGetMaterialxv__II_3II
  (JNIEnv *_env, jobject _this, jint face, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetMaterialxv(
        (GLenum)face,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetMaterialxv ( GLenum face, GLenum pname, GLfixed *params ) */
static void
android_glGetMaterialxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint face, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_SHININESS)
        case GL_SHININESS:
#endif // defined(GL_SHININESS)
            _needed = 1;
            break;
#if defined(GL_AMBIENT)
        case GL_AMBIENT:
#endif // defined(GL_AMBIENT)
#if defined(GL_DIFFUSE)
        case GL_DIFFUSE:
#endif // defined(GL_DIFFUSE)
#if defined(GL_SPECULAR)
        case GL_SPECULAR:
#endif // defined(GL_SPECULAR)
#if defined(GL_EMISSION)
        case GL_EMISSION:
#endif // defined(GL_EMISSION)
#if defined(GL_AMBIENT_AND_DIFFUSE)
        case GL_AMBIENT_AND_DIFFUSE:
#endif // defined(GL_AMBIENT_AND_DIFFUSE)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glGetMaterialxv(
        (GLenum)face,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetTexEnviv ( GLenum env, GLenum pname, GLint *params ) */
static void
android_glGetTexEnviv__II_3II
  (JNIEnv *_env, jobject _this, jint env, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLint *params_base = (GLint *) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLint *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetTexEnviv(
        (GLenum)env,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetTexEnviv ( GLenum env, GLenum pname, GLint *params ) */
static void
android_glGetTexEnviv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint env, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    params = (GLint *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glGetTexEnviv(
        (GLenum)env,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetTexEnvxv ( GLenum env, GLenum pname, GLfixed *params ) */
static void
android_glGetTexEnvxv__II_3II
  (JNIEnv *_env, jobject _this, jint env, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetTexEnvxv(
        (GLenum)env,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetTexEnvxv ( GLenum env, GLenum pname, GLfixed *params ) */
static void
android_glGetTexEnvxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint env, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glGetTexEnvxv(
        (GLenum)env,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetTexParameterfv ( GLenum target, GLenum pname, GLfloat *params ) */
static void
android_glGetTexParameterfv__II_3FI
  (JNIEnv *_env, jobject _this, jint target, jint pname, jfloatArray params_ref, jint offset) {
    jint _exception = 0;
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetTexParameterfv(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetTexParameterfv ( GLenum target, GLenum pname, GLfloat *params ) */
static void
android_glGetTexParameterfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glGetTexParameterfv(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetTexParameteriv ( GLenum target, GLenum pname, GLint *params ) */
static void
android_glGetTexParameteriv__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLint *params_base = (GLint *) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLint *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetTexParameteriv(
        (GLenum)target,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetTexParameteriv ( GLenum target, GLenum pname, GLint *params ) */
static void
android_glGetTexParameteriv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    params = (GLint *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glGetTexParameteriv(
        (GLenum)target,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* void glGetTexParameterxv ( GLenum target, GLenum pname, GLfixed *params ) */
static void
android_glGetTexParameterxv__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    jint _exception = 0;
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glGetTexParameterxv(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            _exception ? JNI_ABORT: 0);
    }
}

/* void glGetTexParameterxv ( GLenum target, GLenum pname, GLfixed *params ) */
static void
android_glGetTexParameterxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jint _exception = 0;
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _exception = 1;
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glGetTexParameterxv(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, _exception ? JNI_FALSE : JNI_TRUE);
    }
}

/* GLboolean glIsBuffer ( GLuint buffer ) */
static jboolean
android_glIsBuffer__I
  (JNIEnv *_env, jobject _this, jint buffer) {
    GLboolean _returnValue;
    _returnValue = glIsBuffer(
        (GLuint)buffer
    );
    return _returnValue;
}

/* GLboolean glIsEnabled ( GLenum cap ) */
static jboolean
android_glIsEnabled__I
  (JNIEnv *_env, jobject _this, jint cap) {
    GLboolean _returnValue;
    _returnValue = glIsEnabled(
        (GLenum)cap
    );
    return _returnValue;
}

/* GLboolean glIsTexture ( GLuint texture ) */
static jboolean
android_glIsTexture__I
  (JNIEnv *_env, jobject _this, jint texture) {
    GLboolean _returnValue;
    _returnValue = glIsTexture(
        (GLuint)texture
    );
    return _returnValue;
}

/* void glNormalPointer ( GLenum type, GLsizei stride, GLint offset ) */
static void
android_glNormalPointer__III
  (JNIEnv *_env, jobject _this, jint type, jint stride, jint offset) {
    glNormalPointer(
        (GLenum)type,
        (GLsizei)stride,
        (const GLvoid *)offset
    );
}

/* void glPointParameterf ( GLenum pname, GLfloat param ) */
static void
android_glPointParameterf__IF
  (JNIEnv *_env, jobject _this, jint pname, jfloat param) {
    glPointParameterf(
        (GLenum)pname,
        (GLfloat)param
    );
}

/* void glPointParameterfv ( GLenum pname, const GLfloat *params ) */
static void
android_glPointParameterfv__I_3FI
  (JNIEnv *_env, jobject _this, jint pname, jfloatArray params_ref, jint offset) {
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glPointParameterfv(
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glPointParameterfv ( GLenum pname, const GLfloat *params ) */
static void
android_glPointParameterfv__ILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glPointParameterfv(
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glPointParameterx ( GLenum pname, GLfixed param ) */
static void
android_glPointParameterx__II
  (JNIEnv *_env, jobject _this, jint pname, jint param) {
    glPointParameterx(
        (GLenum)pname,
        (GLfixed)param
    );
}

/* void glPointParameterxv ( GLenum pname, const GLfixed *params ) */
static void
android_glPointParameterxv__I_3II
  (JNIEnv *_env, jobject _this, jint pname, jintArray params_ref, jint offset) {
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glPointParameterxv(
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glPointParameterxv ( GLenum pname, const GLfixed *params ) */
static void
android_glPointParameterxv__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glPointParameterxv(
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glPointSizePointerOES ( GLenum type, GLsizei stride, const GLvoid *pointer ) */
static void
android_glPointSizePointerOES__IILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint type, jint stride, jobject pointer_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLvoid *pointer = (GLvoid *) 0;

    pointer = (GLvoid *)getPointer(_env, pointer_buf, &_array, &_remaining);
    glPointSizePointerOES(
        (GLenum)type,
        (GLsizei)stride,
        (GLvoid *)pointer
    );
    if (_array) {
        releasePointer(_env, _array, pointer, JNI_FALSE);
    }
}

/* void glTexCoordPointer ( GLint size, GLenum type, GLsizei stride, GLint offset ) */
static void
android_glTexCoordPointer__IIII
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jint offset) {
    glTexCoordPointer(
        (GLint)size,
        (GLenum)type,
        (GLsizei)stride,
        (const GLvoid *)offset
    );
}

/* void glTexEnvi ( GLenum target, GLenum pname, GLint param ) */
static void
android_glTexEnvi__III
  (JNIEnv *_env, jobject _this, jint target, jint pname, jint param) {
    glTexEnvi(
        (GLenum)target,
        (GLenum)pname,
        (GLint)param
    );
}

/* void glTexEnviv ( GLenum target, GLenum pname, const GLint *params ) */
static void
android_glTexEnviv__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    GLint *params_base = (GLint *) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "length - offset < needed");
        goto exit;
    }
    params_base = (GLint *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glTexEnviv(
        (GLenum)target,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glTexEnviv ( GLenum target, GLenum pname, const GLint *params ) */
static void
android_glTexEnviv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    params = (GLint *)getPointer(_env, params_buf, &_array, &_remaining);
    int _needed;
    switch (pname) {
#if defined(GL_TEXTURE_ENV_MODE)
        case GL_TEXTURE_ENV_MODE:
#endif // defined(GL_TEXTURE_ENV_MODE)
#if defined(GL_COMBINE_RGB)
        case GL_COMBINE_RGB:
#endif // defined(GL_COMBINE_RGB)
#if defined(GL_COMBINE_ALPHA)
        case GL_COMBINE_ALPHA:
#endif // defined(GL_COMBINE_ALPHA)
            _needed = 1;
            break;
#if defined(GL_TEXTURE_ENV_COLOR)
        case GL_TEXTURE_ENV_COLOR:
#endif // defined(GL_TEXTURE_ENV_COLOR)
            _needed = 4;
            break;
        default:
            _needed = 0;
            break;
    }
    if (_remaining < _needed) {
        _env->ThrowNew(IAEClass, "remaining() < needed");
        goto exit;
    }
    glTexEnviv(
        (GLenum)target,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glTexParameterfv ( GLenum target, GLenum pname, const GLfloat *params ) */
static void
android_glTexParameterfv__II_3FI
  (JNIEnv *_env, jobject _this, jint target, jint pname, jfloatArray params_ref, jint offset) {
    GLfloat *params_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glTexParameterfv(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glTexParameterfv ( GLenum target, GLenum pname, const GLfloat *params ) */
static void
android_glTexParameterfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *params = (GLfloat *) 0;

    params = (GLfloat *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glTexParameterfv(
        (GLenum)target,
        (GLenum)pname,
        (GLfloat *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glTexParameteri ( GLenum target, GLenum pname, GLint param ) */
static void
android_glTexParameteri__III
  (JNIEnv *_env, jobject _this, jint target, jint pname, jint param) {
    glTexParameteri(
        (GLenum)target,
        (GLenum)pname,
        (GLint)param
    );
}

/* void glTexParameteriv ( GLenum target, GLenum pname, const GLint *params ) */
static void
android_glTexParameteriv__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    GLint *params_base = (GLint *) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLint *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glTexParameteriv(
        (GLenum)target,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glTexParameteriv ( GLenum target, GLenum pname, const GLint *params ) */
static void
android_glTexParameteriv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLint *params = (GLint *) 0;

    params = (GLint *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glTexParameteriv(
        (GLenum)target,
        (GLenum)pname,
        (GLint *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glTexParameterxv ( GLenum target, GLenum pname, const GLfixed *params ) */
static void
android_glTexParameterxv__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    GLfixed *params_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    if (!params_ref) {
        _env->ThrowNew(IAEClass, "params == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(params_ref) - offset;
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "length - offset < 1");
        goto exit;
    }
    params_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(params_ref, (jboolean *)0);
    params = params_base + offset;

    glTexParameterxv(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (params_base) {
        _env->ReleasePrimitiveArrayCritical(params_ref, params_base,
            JNI_ABORT);
    }
}

/* void glTexParameterxv ( GLenum target, GLenum pname, const GLfixed *params ) */
static void
android_glTexParameterxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *params = (GLfixed *) 0;

    params = (GLfixed *)getPointer(_env, params_buf, &_array, &_remaining);
    if (_remaining < 1) {
        _env->ThrowNew(IAEClass, "remaining() < 1");
        goto exit;
    }
    glTexParameterxv(
        (GLenum)target,
        (GLenum)pname,
        (GLfixed *)params
    );

exit:
    if (_array) {
        releasePointer(_env, _array, params, JNI_FALSE);
    }
}

/* void glVertexPointer ( GLint size, GLenum type, GLsizei stride, GLint offset ) */
static void
android_glVertexPointer__IIII
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jint offset) {
    glVertexPointer(
        (GLint)size,
        (GLenum)type,
        (GLsizei)stride,
        (const GLvoid *)offset
    );
}

/* void glCurrentPaletteMatrixOES ( GLuint matrixpaletteindex ) */
static void
android_glCurrentPaletteMatrixOES__I
  (JNIEnv *_env, jobject _this, jint matrixpaletteindex) {
    _env->ThrowNew(UOEClass,
        "glCurrentPaletteMatrixOES");
}

/* void glDrawTexfOES ( GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height ) */
static void
android_glDrawTexfOES__FFFFF
  (JNIEnv *_env, jobject _this, jfloat x, jfloat y, jfloat z, jfloat width, jfloat height) {
    glDrawTexfOES(
        (GLfloat)x,
        (GLfloat)y,
        (GLfloat)z,
        (GLfloat)width,
        (GLfloat)height
    );
}

/* void glDrawTexfvOES ( const GLfloat *coords ) */
static void
android_glDrawTexfvOES___3FI
  (JNIEnv *_env, jobject _this, jfloatArray coords_ref, jint offset) {
    GLfloat *coords_base = (GLfloat *) 0;
    jint _remaining;
    GLfloat *coords = (GLfloat *) 0;

    if (!coords_ref) {
        _env->ThrowNew(IAEClass, "coords == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(coords_ref) - offset;
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "length - offset < 5");
        goto exit;
    }
    coords_base = (GLfloat *)
        _env->GetPrimitiveArrayCritical(coords_ref, (jboolean *)0);
    coords = coords_base + offset;

    glDrawTexfvOES(
        (GLfloat *)coords
    );

exit:
    if (coords_base) {
        _env->ReleasePrimitiveArrayCritical(coords_ref, coords_base,
            JNI_ABORT);
    }
}

/* void glDrawTexfvOES ( const GLfloat *coords ) */
static void
android_glDrawTexfvOES__Ljava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jobject coords_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfloat *coords = (GLfloat *) 0;

    coords = (GLfloat *)getPointer(_env, coords_buf, &_array, &_remaining);
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "remaining() < 5");
        goto exit;
    }
    glDrawTexfvOES(
        (GLfloat *)coords
    );

exit:
    if (_array) {
        releasePointer(_env, _array, coords, JNI_FALSE);
    }
}

/* void glDrawTexiOES ( GLint x, GLint y, GLint z, GLint width, GLint height ) */
static void
android_glDrawTexiOES__IIIII
  (JNIEnv *_env, jobject _this, jint x, jint y, jint z, jint width, jint height) {
    glDrawTexiOES(
        (GLint)x,
        (GLint)y,
        (GLint)z,
        (GLint)width,
        (GLint)height
    );
}

/* void glDrawTexivOES ( const GLint *coords ) */
static void
android_glDrawTexivOES___3II
  (JNIEnv *_env, jobject _this, jintArray coords_ref, jint offset) {
    GLint *coords_base = (GLint *) 0;
    jint _remaining;
    GLint *coords = (GLint *) 0;

    if (!coords_ref) {
        _env->ThrowNew(IAEClass, "coords == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(coords_ref) - offset;
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "length - offset < 5");
        goto exit;
    }
    coords_base = (GLint *)
        _env->GetPrimitiveArrayCritical(coords_ref, (jboolean *)0);
    coords = coords_base + offset;

    glDrawTexivOES(
        (GLint *)coords
    );

exit:
    if (coords_base) {
        _env->ReleasePrimitiveArrayCritical(coords_ref, coords_base,
            JNI_ABORT);
    }
}

/* void glDrawTexivOES ( const GLint *coords ) */
static void
android_glDrawTexivOES__Ljava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jobject coords_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLint *coords = (GLint *) 0;

    coords = (GLint *)getPointer(_env, coords_buf, &_array, &_remaining);
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "remaining() < 5");
        goto exit;
    }
    glDrawTexivOES(
        (GLint *)coords
    );

exit:
    if (_array) {
        releasePointer(_env, _array, coords, JNI_FALSE);
    }
}

/* void glDrawTexsOES ( GLshort x, GLshort y, GLshort z, GLshort width, GLshort height ) */
static void
android_glDrawTexsOES__SSSSS
  (JNIEnv *_env, jobject _this, jshort x, jshort y, jshort z, jshort width, jshort height) {
    glDrawTexsOES(
        (GLshort)x,
        (GLshort)y,
        (GLshort)z,
        (GLshort)width,
        (GLshort)height
    );
}

/* void glDrawTexsvOES ( const GLshort *coords ) */
static void
android_glDrawTexsvOES___3SI
  (JNIEnv *_env, jobject _this, jshortArray coords_ref, jint offset) {
    GLshort *coords_base = (GLshort *) 0;
    jint _remaining;
    GLshort *coords = (GLshort *) 0;

    if (!coords_ref) {
        _env->ThrowNew(IAEClass, "coords == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(coords_ref) - offset;
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "length - offset < 5");
        goto exit;
    }
    coords_base = (GLshort *)
        _env->GetPrimitiveArrayCritical(coords_ref, (jboolean *)0);
    coords = coords_base + offset;

    glDrawTexsvOES(
        (GLshort *)coords
    );

exit:
    if (coords_base) {
        _env->ReleasePrimitiveArrayCritical(coords_ref, coords_base,
            JNI_ABORT);
    }
}

/* void glDrawTexsvOES ( const GLshort *coords ) */
static void
android_glDrawTexsvOES__Ljava_nio_ShortBuffer_2
  (JNIEnv *_env, jobject _this, jobject coords_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLshort *coords = (GLshort *) 0;

    coords = (GLshort *)getPointer(_env, coords_buf, &_array, &_remaining);
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "remaining() < 5");
        goto exit;
    }
    glDrawTexsvOES(
        (GLshort *)coords
    );

exit:
    if (_array) {
        releasePointer(_env, _array, coords, JNI_FALSE);
    }
}

/* void glDrawTexxOES ( GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height ) */
static void
android_glDrawTexxOES__IIIII
  (JNIEnv *_env, jobject _this, jint x, jint y, jint z, jint width, jint height) {
    glDrawTexxOES(
        (GLfixed)x,
        (GLfixed)y,
        (GLfixed)z,
        (GLfixed)width,
        (GLfixed)height
    );
}

/* void glDrawTexxvOES ( const GLfixed *coords ) */
static void
android_glDrawTexxvOES___3II
  (JNIEnv *_env, jobject _this, jintArray coords_ref, jint offset) {
    GLfixed *coords_base = (GLfixed *) 0;
    jint _remaining;
    GLfixed *coords = (GLfixed *) 0;

    if (!coords_ref) {
        _env->ThrowNew(IAEClass, "coords == null");
        goto exit;
    }
    if (offset < 0) {
        _env->ThrowNew(IAEClass, "offset < 0");
        goto exit;
    }
    _remaining = _env->GetArrayLength(coords_ref) - offset;
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "length - offset < 5");
        goto exit;
    }
    coords_base = (GLfixed *)
        _env->GetPrimitiveArrayCritical(coords_ref, (jboolean *)0);
    coords = coords_base + offset;

    glDrawTexxvOES(
        (GLfixed *)coords
    );

exit:
    if (coords_base) {
        _env->ReleasePrimitiveArrayCritical(coords_ref, coords_base,
            JNI_ABORT);
    }
}

/* void glDrawTexxvOES ( const GLfixed *coords ) */
static void
android_glDrawTexxvOES__Ljava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jobject coords_buf) {
    jarray _array = (jarray) 0;
    jint _remaining;
    GLfixed *coords = (GLfixed *) 0;

    coords = (GLfixed *)getPointer(_env, coords_buf, &_array, &_remaining);
    if (_remaining < 5) {
        _env->ThrowNew(IAEClass, "remaining() < 5");
        goto exit;
    }
    glDrawTexxvOES(
        (GLfixed *)coords
    );

exit:
    if (_array) {
        releasePointer(_env, _array, coords, JNI_FALSE);
    }
}

/* void glLoadPaletteFromModelViewMatrixOES ( void ) */
static void
android_glLoadPaletteFromModelViewMatrixOES__
  (JNIEnv *_env, jobject _this) {
    _env->ThrowNew(UOEClass,
        "glLoadPaletteFromModelViewMatrixOES");
}

/* void glMatrixIndexPointerOES ( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer ) */
static void
android_glMatrixIndexPointerOES__IIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jobject pointer_buf) {
    _env->ThrowNew(UOEClass,
        "glMatrixIndexPointerOES");
}

/* void glMatrixIndexPointerOES ( GLint size, GLenum type, GLsizei stride, GLint offset ) */
static void
android_glMatrixIndexPointerOES__IIII
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jint offset) {
    _env->ThrowNew(UOEClass,
        "glMatrixIndexPointerOES");
}

/* void glWeightPointerOES ( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer ) */
static void
android_glWeightPointerOES__IIILjava_nio_Buffer_2
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jobject pointer_buf) {
    _env->ThrowNew(UOEClass,
        "glWeightPointerOES");
}

/* void glWeightPointerOES ( GLint size, GLenum type, GLsizei stride, GLint offset ) */
static void
android_glWeightPointerOES__IIII
  (JNIEnv *_env, jobject _this, jint size, jint type, jint stride, jint offset) {
    _env->ThrowNew(UOEClass,
        "glWeightPointerOES");
}

/* void glBindFramebufferOES ( GLint target, GLint framebuffer ) */
static void
android_glBindFramebufferOES__II
  (JNIEnv *_env, jobject _this, jint target, jint framebuffer) {
    _env->ThrowNew(UOEClass,
        "glBindFramebufferOES");
}

/* void glBindRenderbufferOES ( GLint target, GLint renderbuffer ) */
static void
android_glBindRenderbufferOES__II
  (JNIEnv *_env, jobject _this, jint target, jint renderbuffer) {
    _env->ThrowNew(UOEClass,
        "glBindRenderbufferOES");
}

/* void glBlendEquation ( GLint mode ) */
static void
android_glBlendEquation__I
  (JNIEnv *_env, jobject _this, jint mode) {
    _env->ThrowNew(UOEClass,
        "glBlendEquation");
}

/* void glBlendEquationSeparate ( GLint modeRGB, GLint modeAlpha ) */
static void
android_glBlendEquationSeparate__II
  (JNIEnv *_env, jobject _this, jint modeRGB, jint modeAlpha) {
    _env->ThrowNew(UOEClass,
        "glBlendEquationSeparate");
}

/* void glBlendFuncSeparate ( GLint srcRGB, GLint dstRGB, GLint srcAlpha, GLint dstAlpha ) */
static void
android_glBlendFuncSeparate__IIII
  (JNIEnv *_env, jobject _this, jint srcRGB, jint dstRGB, jint srcAlpha, jint dstAlpha) {
    _env->ThrowNew(UOEClass,
        "glBlendFuncSeparate");
}

/* GLint glCheckFramebufferStatusOES ( GLint target ) */
static jint
android_glCheckFramebufferStatusOES__I
  (JNIEnv *_env, jobject _this, jint target) {
    _env->ThrowNew(UOEClass,
        "glCheckFramebufferStatusOES");
    return 0;
}

/* void glDeleteFramebuffersOES ( GLint n, GLint *framebuffers ) */
static void
android_glDeleteFramebuffersOES__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray framebuffers_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glDeleteFramebuffersOES");
}

/* void glDeleteFramebuffersOES ( GLint n, GLint *framebuffers ) */
static void
android_glDeleteFramebuffersOES__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject framebuffers_buf) {
    _env->ThrowNew(UOEClass,
        "glDeleteFramebuffersOES");
}

/* void glDeleteRenderbuffersOES ( GLint n, GLint *renderbuffers ) */
static void
android_glDeleteRenderbuffersOES__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray renderbuffers_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glDeleteRenderbuffersOES");
}

/* void glDeleteRenderbuffersOES ( GLint n, GLint *renderbuffers ) */
static void
android_glDeleteRenderbuffersOES__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject renderbuffers_buf) {
    _env->ThrowNew(UOEClass,
        "glDeleteRenderbuffersOES");
}

/* void glFramebufferRenderbufferOES ( GLint target, GLint attachment, GLint renderbuffertarget, GLint renderbuffer ) */
static void
android_glFramebufferRenderbufferOES__IIII
  (JNIEnv *_env, jobject _this, jint target, jint attachment, jint renderbuffertarget, jint renderbuffer) {
    _env->ThrowNew(UOEClass,
        "glFramebufferRenderbufferOES");
}

/* void glFramebufferTexture2DOES ( GLint target, GLint attachment, GLint textarget, GLint texture, GLint level ) */
static void
android_glFramebufferTexture2DOES__IIIII
  (JNIEnv *_env, jobject _this, jint target, jint attachment, jint textarget, jint texture, jint level) {
    _env->ThrowNew(UOEClass,
        "glFramebufferTexture2DOES");
}

/* void glGenerateMipmapOES ( GLint target ) */
static void
android_glGenerateMipmapOES__I
  (JNIEnv *_env, jobject _this, jint target) {
    _env->ThrowNew(UOEClass,
        "glGenerateMipmapOES");
}

/* void glGenFramebuffersOES ( GLint n, GLint *framebuffers ) */
static void
android_glGenFramebuffersOES__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray framebuffers_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGenFramebuffersOES");
}

/* void glGenFramebuffersOES ( GLint n, GLint *framebuffers ) */
static void
android_glGenFramebuffersOES__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject framebuffers_buf) {
    _env->ThrowNew(UOEClass,
        "glGenFramebuffersOES");
}

/* void glGenRenderbuffersOES ( GLint n, GLint *renderbuffers ) */
static void
android_glGenRenderbuffersOES__I_3II
  (JNIEnv *_env, jobject _this, jint n, jintArray renderbuffers_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGenRenderbuffersOES");
}

/* void glGenRenderbuffersOES ( GLint n, GLint *renderbuffers ) */
static void
android_glGenRenderbuffersOES__ILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint n, jobject renderbuffers_buf) {
    _env->ThrowNew(UOEClass,
        "glGenRenderbuffersOES");
}

/* void glGetFramebufferAttachmentParameterivOES ( GLint target, GLint attachment, GLint pname, GLint *params ) */
static void
android_glGetFramebufferAttachmentParameterivOES__III_3II
  (JNIEnv *_env, jobject _this, jint target, jint attachment, jint pname, jintArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGetFramebufferAttachmentParameterivOES");
}

/* void glGetFramebufferAttachmentParameterivOES ( GLint target, GLint attachment, GLint pname, GLint *params ) */
static void
android_glGetFramebufferAttachmentParameterivOES__IIILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint attachment, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glGetFramebufferAttachmentParameterivOES");
}

/* void glGetRenderbufferParameterivOES ( GLint target, GLint pname, GLint *params ) */
static void
android_glGetRenderbufferParameterivOES__II_3II
  (JNIEnv *_env, jobject _this, jint target, jint pname, jintArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGetRenderbufferParameterivOES");
}

/* void glGetRenderbufferParameterivOES ( GLint target, GLint pname, GLint *params ) */
static void
android_glGetRenderbufferParameterivOES__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint target, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glGetRenderbufferParameterivOES");
}

/* void glGetTexGenfv ( GLint coord, GLint pname, GLfloat *params ) */
static void
android_glGetTexGenfv__II_3FI
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jfloatArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGetTexGenfv");
}

/* void glGetTexGenfv ( GLint coord, GLint pname, GLfloat *params ) */
static void
android_glGetTexGenfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glGetTexGenfv");
}

/* void glGetTexGeniv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glGetTexGeniv__II_3II
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jintArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGetTexGeniv");
}

/* void glGetTexGeniv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glGetTexGeniv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glGetTexGeniv");
}

/* void glGetTexGenxv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glGetTexGenxv__II_3II
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jintArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glGetTexGenxv");
}

/* void glGetTexGenxv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glGetTexGenxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glGetTexGenxv");
}

/* GLboolean glIsFramebufferOES ( GLint framebuffer ) */
static jboolean
android_glIsFramebufferOES__I
  (JNIEnv *_env, jobject _this, jint framebuffer) {
    _env->ThrowNew(UOEClass,
        "glIsFramebufferOES");
    return JNI_FALSE;
}

/* GLboolean glIsRenderbufferOES ( GLint renderbuffer ) */
static jboolean
android_glIsRenderbufferOES__I
  (JNIEnv *_env, jobject _this, jint renderbuffer) {
    _env->ThrowNew(UOEClass,
        "glIsRenderbufferOES");
    return JNI_FALSE;
}

/* void glRenderbufferStorageOES ( GLint target, GLint internalformat, GLint width, GLint height ) */
static void
android_glRenderbufferStorageOES__IIII
  (JNIEnv *_env, jobject _this, jint target, jint internalformat, jint width, jint height) {
    _env->ThrowNew(UOEClass,
        "glRenderbufferStorageOES");
}

/* void glTexGenf ( GLint coord, GLint pname, GLfloat param ) */
static void
android_glTexGenf__IIF
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jfloat param) {
    _env->ThrowNew(UOEClass,
        "glTexGenf");
}

/* void glTexGenfv ( GLint coord, GLint pname, GLfloat *params ) */
static void
android_glTexGenfv__II_3FI
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jfloatArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glTexGenfv");
}

/* void glTexGenfv ( GLint coord, GLint pname, GLfloat *params ) */
static void
android_glTexGenfv__IILjava_nio_FloatBuffer_2
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glTexGenfv");
}

/* void glTexGeni ( GLint coord, GLint pname, GLint param ) */
static void
android_glTexGeni__III
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jint param) {
    _env->ThrowNew(UOEClass,
        "glTexGeni");
}

/* void glTexGeniv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glTexGeniv__II_3II
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jintArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glTexGeniv");
}

/* void glTexGeniv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glTexGeniv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glTexGeniv");
}

/* void glTexGenx ( GLint coord, GLint pname, GLint param ) */
static void
android_glTexGenx__III
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jint param) {
    _env->ThrowNew(UOEClass,
        "glTexGenx");
}

/* void glTexGenxv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glTexGenxv__II_3II
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jintArray params_ref, jint offset) {
    _env->ThrowNew(UOEClass,
        "glTexGenxv");
}

/* void glTexGenxv ( GLint coord, GLint pname, GLint *params ) */
static void
android_glTexGenxv__IILjava_nio_IntBuffer_2
  (JNIEnv *_env, jobject _this, jint coord, jint pname, jobject params_buf) {
    _env->ThrowNew(UOEClass,
        "glTexGenxv");
}

static const char *classPathName = "com/google/android/gles_jni/GLImpl";

static JNINativeMethod methods[] = {
{"_nativeClassInit", "()V", (void*)nativeClassInit },
{"glActiveTexture", "(I)V", (void *) android_glActiveTexture__I },
{"glAlphaFunc", "(IF)V", (void *) android_glAlphaFunc__IF },
{"glAlphaFuncx", "(II)V", (void *) android_glAlphaFuncx__II },
{"glBindTexture", "(II)V", (void *) android_glBindTexture__II },
{"glBlendFunc", "(II)V", (void *) android_glBlendFunc__II },
{"glClear", "(I)V", (void *) android_glClear__I },
{"glClearColor", "(FFFF)V", (void *) android_glClearColor__FFFF },
{"glClearColorx", "(IIII)V", (void *) android_glClearColorx__IIII },
{"glClearDepthf", "(F)V", (void *) android_glClearDepthf__F },
{"glClearDepthx", "(I)V", (void *) android_glClearDepthx__I },
{"glClearStencil", "(I)V", (void *) android_glClearStencil__I },
{"glClientActiveTexture", "(I)V", (void *) android_glClientActiveTexture__I },
{"glColor4f", "(FFFF)V", (void *) android_glColor4f__FFFF },
{"glColor4x", "(IIII)V", (void *) android_glColor4x__IIII },
{"glColorMask", "(ZZZZ)V", (void *) android_glColorMask__ZZZZ },
{"glColorPointerBounds", "(IIILjava/nio/Buffer;I)V", (void *) android_glColorPointerBounds__IIILjava_nio_Buffer_2I },
{"glCompressedTexImage2D", "(IIIIIIILjava/nio/Buffer;)V", (void *) android_glCompressedTexImage2D__IIIIIIILjava_nio_Buffer_2 },
{"glCompressedTexSubImage2D", "(IIIIIIIILjava/nio/Buffer;)V", (void *) android_glCompressedTexSubImage2D__IIIIIIIILjava_nio_Buffer_2 },
{"glCopyTexImage2D", "(IIIIIIII)V", (void *) android_glCopyTexImage2D__IIIIIIII },
{"glCopyTexSubImage2D", "(IIIIIIII)V", (void *) android_glCopyTexSubImage2D__IIIIIIII },
{"glCullFace", "(I)V", (void *) android_glCullFace__I },
{"glDeleteTextures", "(I[II)V", (void *) android_glDeleteTextures__I_3II },
{"glDeleteTextures", "(ILjava/nio/IntBuffer;)V", (void *) android_glDeleteTextures__ILjava_nio_IntBuffer_2 },
{"glDepthFunc", "(I)V", (void *) android_glDepthFunc__I },
{"glDepthMask", "(Z)V", (void *) android_glDepthMask__Z },
{"glDepthRangef", "(FF)V", (void *) android_glDepthRangef__FF },
{"glDepthRangex", "(II)V", (void *) android_glDepthRangex__II },
{"glDisable", "(I)V", (void *) android_glDisable__I },
{"glDisableClientState", "(I)V", (void *) android_glDisableClientState__I },
{"glDrawArrays", "(III)V", (void *) android_glDrawArrays__III },
{"glDrawElements", "(IIILjava/nio/Buffer;)V", (void *) android_glDrawElements__IIILjava_nio_Buffer_2 },
{"glEnable", "(I)V", (void *) android_glEnable__I },
{"glEnableClientState", "(I)V", (void *) android_glEnableClientState__I },
{"glFinish", "()V", (void *) android_glFinish__ },
{"glFlush", "()V", (void *) android_glFlush__ },
{"glFogf", "(IF)V", (void *) android_glFogf__IF },
{"glFogfv", "(I[FI)V", (void *) android_glFogfv__I_3FI },
{"glFogfv", "(ILjava/nio/FloatBuffer;)V", (void *) android_glFogfv__ILjava_nio_FloatBuffer_2 },
{"glFogx", "(II)V", (void *) android_glFogx__II },
{"glFogxv", "(I[II)V", (void *) android_glFogxv__I_3II },
{"glFogxv", "(ILjava/nio/IntBuffer;)V", (void *) android_glFogxv__ILjava_nio_IntBuffer_2 },
{"glFrontFace", "(I)V", (void *) android_glFrontFace__I },
{"glFrustumf", "(FFFFFF)V", (void *) android_glFrustumf__FFFFFF },
{"glFrustumx", "(IIIIII)V", (void *) android_glFrustumx__IIIIII },
{"glGenTextures", "(I[II)V", (void *) android_glGenTextures__I_3II },
{"glGenTextures", "(ILjava/nio/IntBuffer;)V", (void *) android_glGenTextures__ILjava_nio_IntBuffer_2 },
{"glGetError", "()I", (void *) android_glGetError__ },
{"glGetIntegerv", "(I[II)V", (void *) android_glGetIntegerv__I_3II },
{"glGetIntegerv", "(ILjava/nio/IntBuffer;)V", (void *) android_glGetIntegerv__ILjava_nio_IntBuffer_2 },
{"_glGetString", "(I)Ljava/lang/String;", (void *) android_glGetString },
{"glHint", "(II)V", (void *) android_glHint__II },
{"glLightModelf", "(IF)V", (void *) android_glLightModelf__IF },
{"glLightModelfv", "(I[FI)V", (void *) android_glLightModelfv__I_3FI },
{"glLightModelfv", "(ILjava/nio/FloatBuffer;)V", (void *) android_glLightModelfv__ILjava_nio_FloatBuffer_2 },
{"glLightModelx", "(II)V", (void *) android_glLightModelx__II },
{"glLightModelxv", "(I[II)V", (void *) android_glLightModelxv__I_3II },
{"glLightModelxv", "(ILjava/nio/IntBuffer;)V", (void *) android_glLightModelxv__ILjava_nio_IntBuffer_2 },
{"glLightf", "(IIF)V", (void *) android_glLightf__IIF },
{"glLightfv", "(II[FI)V", (void *) android_glLightfv__II_3FI },
{"glLightfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glLightfv__IILjava_nio_FloatBuffer_2 },
{"glLightx", "(III)V", (void *) android_glLightx__III },
{"glLightxv", "(II[II)V", (void *) android_glLightxv__II_3II },
{"glLightxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glLightxv__IILjava_nio_IntBuffer_2 },
{"glLineWidth", "(F)V", (void *) android_glLineWidth__F },
{"glLineWidthx", "(I)V", (void *) android_glLineWidthx__I },
{"glLoadIdentity", "()V", (void *) android_glLoadIdentity__ },
{"glLoadMatrixf", "([FI)V", (void *) android_glLoadMatrixf___3FI },
{"glLoadMatrixf", "(Ljava/nio/FloatBuffer;)V", (void *) android_glLoadMatrixf__Ljava_nio_FloatBuffer_2 },
{"glLoadMatrixx", "([II)V", (void *) android_glLoadMatrixx___3II },
{"glLoadMatrixx", "(Ljava/nio/IntBuffer;)V", (void *) android_glLoadMatrixx__Ljava_nio_IntBuffer_2 },
{"glLogicOp", "(I)V", (void *) android_glLogicOp__I },
{"glMaterialf", "(IIF)V", (void *) android_glMaterialf__IIF },
{"glMaterialfv", "(II[FI)V", (void *) android_glMaterialfv__II_3FI },
{"glMaterialfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glMaterialfv__IILjava_nio_FloatBuffer_2 },
{"glMaterialx", "(III)V", (void *) android_glMaterialx__III },
{"glMaterialxv", "(II[II)V", (void *) android_glMaterialxv__II_3II },
{"glMaterialxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glMaterialxv__IILjava_nio_IntBuffer_2 },
{"glMatrixMode", "(I)V", (void *) android_glMatrixMode__I },
{"glMultMatrixf", "([FI)V", (void *) android_glMultMatrixf___3FI },
{"glMultMatrixf", "(Ljava/nio/FloatBuffer;)V", (void *) android_glMultMatrixf__Ljava_nio_FloatBuffer_2 },
{"glMultMatrixx", "([II)V", (void *) android_glMultMatrixx___3II },
{"glMultMatrixx", "(Ljava/nio/IntBuffer;)V", (void *) android_glMultMatrixx__Ljava_nio_IntBuffer_2 },
{"glMultiTexCoord4f", "(IFFFF)V", (void *) android_glMultiTexCoord4f__IFFFF },
{"glMultiTexCoord4x", "(IIIII)V", (void *) android_glMultiTexCoord4x__IIIII },
{"glNormal3f", "(FFF)V", (void *) android_glNormal3f__FFF },
{"glNormal3x", "(III)V", (void *) android_glNormal3x__III },
{"glNormalPointerBounds", "(IILjava/nio/Buffer;I)V", (void *) android_glNormalPointerBounds__IILjava_nio_Buffer_2I },
{"glOrthof", "(FFFFFF)V", (void *) android_glOrthof__FFFFFF },
{"glOrthox", "(IIIIII)V", (void *) android_glOrthox__IIIIII },
{"glPixelStorei", "(II)V", (void *) android_glPixelStorei__II },
{"glPointSize", "(F)V", (void *) android_glPointSize__F },
{"glPointSizex", "(I)V", (void *) android_glPointSizex__I },
{"glPolygonOffset", "(FF)V", (void *) android_glPolygonOffset__FF },
{"glPolygonOffsetx", "(II)V", (void *) android_glPolygonOffsetx__II },
{"glPopMatrix", "()V", (void *) android_glPopMatrix__ },
{"glPushMatrix", "()V", (void *) android_glPushMatrix__ },
{"glReadPixels", "(IIIIIILjava/nio/Buffer;)V", (void *) android_glReadPixels__IIIIIILjava_nio_Buffer_2 },
{"glRotatef", "(FFFF)V", (void *) android_glRotatef__FFFF },
{"glRotatex", "(IIII)V", (void *) android_glRotatex__IIII },
{"glSampleCoverage", "(FZ)V", (void *) android_glSampleCoverage__FZ },
{"glSampleCoveragex", "(IZ)V", (void *) android_glSampleCoveragex__IZ },
{"glScalef", "(FFF)V", (void *) android_glScalef__FFF },
{"glScalex", "(III)V", (void *) android_glScalex__III },
{"glScissor", "(IIII)V", (void *) android_glScissor__IIII },
{"glShadeModel", "(I)V", (void *) android_glShadeModel__I },
{"glStencilFunc", "(III)V", (void *) android_glStencilFunc__III },
{"glStencilMask", "(I)V", (void *) android_glStencilMask__I },
{"glStencilOp", "(III)V", (void *) android_glStencilOp__III },
{"glTexCoordPointerBounds", "(IIILjava/nio/Buffer;I)V", (void *) android_glTexCoordPointerBounds__IIILjava_nio_Buffer_2I },
{"glTexEnvf", "(IIF)V", (void *) android_glTexEnvf__IIF },
{"glTexEnvfv", "(II[FI)V", (void *) android_glTexEnvfv__II_3FI },
{"glTexEnvfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glTexEnvfv__IILjava_nio_FloatBuffer_2 },
{"glTexEnvx", "(III)V", (void *) android_glTexEnvx__III },
{"glTexEnvxv", "(II[II)V", (void *) android_glTexEnvxv__II_3II },
{"glTexEnvxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glTexEnvxv__IILjava_nio_IntBuffer_2 },
{"glTexImage2D", "(IIIIIIIILjava/nio/Buffer;)V", (void *) android_glTexImage2D__IIIIIIIILjava_nio_Buffer_2 },
{"glTexParameterf", "(IIF)V", (void *) android_glTexParameterf__IIF },
{"glTexParameterx", "(III)V", (void *) android_glTexParameterx__III },
{"glTexSubImage2D", "(IIIIIIIILjava/nio/Buffer;)V", (void *) android_glTexSubImage2D__IIIIIIIILjava_nio_Buffer_2 },
{"glTranslatef", "(FFF)V", (void *) android_glTranslatef__FFF },
{"glTranslatex", "(III)V", (void *) android_glTranslatex__III },
{"glVertexPointerBounds", "(IIILjava/nio/Buffer;I)V", (void *) android_glVertexPointerBounds__IIILjava_nio_Buffer_2I },
{"glViewport", "(IIII)V", (void *) android_glViewport__IIII },
{"glQueryMatrixxOES", "([II[II)I", (void *) android_glQueryMatrixxOES___3II_3II },
{"glQueryMatrixxOES", "(Ljava/nio/IntBuffer;Ljava/nio/IntBuffer;)I", (void *) android_glQueryMatrixxOES__Ljava_nio_IntBuffer_2Ljava_nio_IntBuffer_2 },
{"glBindBuffer", "(II)V", (void *) android_glBindBuffer__II },
{"glBufferData", "(IILjava/nio/Buffer;I)V", (void *) android_glBufferData__IILjava_nio_Buffer_2I },
{"glBufferSubData", "(IIILjava/nio/Buffer;)V", (void *) android_glBufferSubData__IIILjava_nio_Buffer_2 },
{"glClipPlanef", "(I[FI)V", (void *) android_glClipPlanef__I_3FI },
{"glClipPlanef", "(ILjava/nio/FloatBuffer;)V", (void *) android_glClipPlanef__ILjava_nio_FloatBuffer_2 },
{"glClipPlanex", "(I[II)V", (void *) android_glClipPlanex__I_3II },
{"glClipPlanex", "(ILjava/nio/IntBuffer;)V", (void *) android_glClipPlanex__ILjava_nio_IntBuffer_2 },
{"glColor4ub", "(BBBB)V", (void *) android_glColor4ub__BBBB },
{"glColorPointer", "(IIII)V", (void *) android_glColorPointer__IIII },
{"glDeleteBuffers", "(I[II)V", (void *) android_glDeleteBuffers__I_3II },
{"glDeleteBuffers", "(ILjava/nio/IntBuffer;)V", (void *) android_glDeleteBuffers__ILjava_nio_IntBuffer_2 },
{"glDrawElements", "(IIII)V", (void *) android_glDrawElements__IIII },
{"glGenBuffers", "(I[II)V", (void *) android_glGenBuffers__I_3II },
{"glGenBuffers", "(ILjava/nio/IntBuffer;)V", (void *) android_glGenBuffers__ILjava_nio_IntBuffer_2 },
{"glGetBooleanv", "(I[ZI)V", (void *) android_glGetBooleanv__I_3ZI },
{"glGetBooleanv", "(ILjava/nio/IntBuffer;)V", (void *) android_glGetBooleanv__ILjava_nio_IntBuffer_2 },
{"glGetBufferParameteriv", "(II[II)V", (void *) android_glGetBufferParameteriv__II_3II },
{"glGetBufferParameteriv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetBufferParameteriv__IILjava_nio_IntBuffer_2 },
{"glGetClipPlanef", "(I[FI)V", (void *) android_glGetClipPlanef__I_3FI },
{"glGetClipPlanef", "(ILjava/nio/FloatBuffer;)V", (void *) android_glGetClipPlanef__ILjava_nio_FloatBuffer_2 },
{"glGetClipPlanex", "(I[II)V", (void *) android_glGetClipPlanex__I_3II },
{"glGetClipPlanex", "(ILjava/nio/IntBuffer;)V", (void *) android_glGetClipPlanex__ILjava_nio_IntBuffer_2 },
{"glGetFixedv", "(I[II)V", (void *) android_glGetFixedv__I_3II },
{"glGetFixedv", "(ILjava/nio/IntBuffer;)V", (void *) android_glGetFixedv__ILjava_nio_IntBuffer_2 },
{"glGetFloatv", "(I[FI)V", (void *) android_glGetFloatv__I_3FI },
{"glGetFloatv", "(ILjava/nio/FloatBuffer;)V", (void *) android_glGetFloatv__ILjava_nio_FloatBuffer_2 },
{"glGetLightfv", "(II[FI)V", (void *) android_glGetLightfv__II_3FI },
{"glGetLightfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glGetLightfv__IILjava_nio_FloatBuffer_2 },
{"glGetLightxv", "(II[II)V", (void *) android_glGetLightxv__II_3II },
{"glGetLightxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetLightxv__IILjava_nio_IntBuffer_2 },
{"glGetMaterialfv", "(II[FI)V", (void *) android_glGetMaterialfv__II_3FI },
{"glGetMaterialfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glGetMaterialfv__IILjava_nio_FloatBuffer_2 },
{"glGetMaterialxv", "(II[II)V", (void *) android_glGetMaterialxv__II_3II },
{"glGetMaterialxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetMaterialxv__IILjava_nio_IntBuffer_2 },
{"glGetTexEnviv", "(II[II)V", (void *) android_glGetTexEnviv__II_3II },
{"glGetTexEnviv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetTexEnviv__IILjava_nio_IntBuffer_2 },
{"glGetTexEnvxv", "(II[II)V", (void *) android_glGetTexEnvxv__II_3II },
{"glGetTexEnvxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetTexEnvxv__IILjava_nio_IntBuffer_2 },
{"glGetTexParameterfv", "(II[FI)V", (void *) android_glGetTexParameterfv__II_3FI },
{"glGetTexParameterfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glGetTexParameterfv__IILjava_nio_FloatBuffer_2 },
{"glGetTexParameteriv", "(II[II)V", (void *) android_glGetTexParameteriv__II_3II },
{"glGetTexParameteriv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetTexParameteriv__IILjava_nio_IntBuffer_2 },
{"glGetTexParameterxv", "(II[II)V", (void *) android_glGetTexParameterxv__II_3II },
{"glGetTexParameterxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetTexParameterxv__IILjava_nio_IntBuffer_2 },
{"glIsBuffer", "(I)Z", (void *) android_glIsBuffer__I },
{"glIsEnabled", "(I)Z", (void *) android_glIsEnabled__I },
{"glIsTexture", "(I)Z", (void *) android_glIsTexture__I },
{"glNormalPointer", "(III)V", (void *) android_glNormalPointer__III },
{"glPointParameterf", "(IF)V", (void *) android_glPointParameterf__IF },
{"glPointParameterfv", "(I[FI)V", (void *) android_glPointParameterfv__I_3FI },
{"glPointParameterfv", "(ILjava/nio/FloatBuffer;)V", (void *) android_glPointParameterfv__ILjava_nio_FloatBuffer_2 },
{"glPointParameterx", "(II)V", (void *) android_glPointParameterx__II },
{"glPointParameterxv", "(I[II)V", (void *) android_glPointParameterxv__I_3II },
{"glPointParameterxv", "(ILjava/nio/IntBuffer;)V", (void *) android_glPointParameterxv__ILjava_nio_IntBuffer_2 },
{"glPointSizePointerOES", "(IILjava/nio/Buffer;)V", (void *) android_glPointSizePointerOES__IILjava_nio_Buffer_2 },
{"glTexCoordPointer", "(IIII)V", (void *) android_glTexCoordPointer__IIII },
{"glTexEnvi", "(III)V", (void *) android_glTexEnvi__III },
{"glTexEnviv", "(II[II)V", (void *) android_glTexEnviv__II_3II },
{"glTexEnviv", "(IILjava/nio/IntBuffer;)V", (void *) android_glTexEnviv__IILjava_nio_IntBuffer_2 },
{"glTexParameterfv", "(II[FI)V", (void *) android_glTexParameterfv__II_3FI },
{"glTexParameterfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glTexParameterfv__IILjava_nio_FloatBuffer_2 },
{"glTexParameteri", "(III)V", (void *) android_glTexParameteri__III },
{"glTexParameteriv", "(II[II)V", (void *) android_glTexParameteriv__II_3II },
{"glTexParameteriv", "(IILjava/nio/IntBuffer;)V", (void *) android_glTexParameteriv__IILjava_nio_IntBuffer_2 },
{"glTexParameterxv", "(II[II)V", (void *) android_glTexParameterxv__II_3II },
{"glTexParameterxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glTexParameterxv__IILjava_nio_IntBuffer_2 },
{"glVertexPointer", "(IIII)V", (void *) android_glVertexPointer__IIII },
{"glCurrentPaletteMatrixOES", "(I)V", (void *) android_glCurrentPaletteMatrixOES__I },
{"glDrawTexfOES", "(FFFFF)V", (void *) android_glDrawTexfOES__FFFFF },
{"glDrawTexfvOES", "([FI)V", (void *) android_glDrawTexfvOES___3FI },
{"glDrawTexfvOES", "(Ljava/nio/FloatBuffer;)V", (void *) android_glDrawTexfvOES__Ljava_nio_FloatBuffer_2 },
{"glDrawTexiOES", "(IIIII)V", (void *) android_glDrawTexiOES__IIIII },
{"glDrawTexivOES", "([II)V", (void *) android_glDrawTexivOES___3II },
{"glDrawTexivOES", "(Ljava/nio/IntBuffer;)V", (void *) android_glDrawTexivOES__Ljava_nio_IntBuffer_2 },
{"glDrawTexsOES", "(SSSSS)V", (void *) android_glDrawTexsOES__SSSSS },
{"glDrawTexsvOES", "([SI)V", (void *) android_glDrawTexsvOES___3SI },
{"glDrawTexsvOES", "(Ljava/nio/ShortBuffer;)V", (void *) android_glDrawTexsvOES__Ljava_nio_ShortBuffer_2 },
{"glDrawTexxOES", "(IIIII)V", (void *) android_glDrawTexxOES__IIIII },
{"glDrawTexxvOES", "([II)V", (void *) android_glDrawTexxvOES___3II },
{"glDrawTexxvOES", "(Ljava/nio/IntBuffer;)V", (void *) android_glDrawTexxvOES__Ljava_nio_IntBuffer_2 },
{"glLoadPaletteFromModelViewMatrixOES", "()V", (void *) android_glLoadPaletteFromModelViewMatrixOES__ },
{"glMatrixIndexPointerOES", "(IIILjava/nio/Buffer;)V", (void *) android_glMatrixIndexPointerOES__IIILjava_nio_Buffer_2 },
{"glMatrixIndexPointerOES", "(IIII)V", (void *) android_glMatrixIndexPointerOES__IIII },
{"glWeightPointerOES", "(IIILjava/nio/Buffer;)V", (void *) android_glWeightPointerOES__IIILjava_nio_Buffer_2 },
{"glWeightPointerOES", "(IIII)V", (void *) android_glWeightPointerOES__IIII },
{"glBindFramebufferOES", "(II)V", (void *) android_glBindFramebufferOES__II },
{"glBindRenderbufferOES", "(II)V", (void *) android_glBindRenderbufferOES__II },
{"glBlendEquation", "(I)V", (void *) android_glBlendEquation__I },
{"glBlendEquationSeparate", "(II)V", (void *) android_glBlendEquationSeparate__II },
{"glBlendFuncSeparate", "(IIII)V", (void *) android_glBlendFuncSeparate__IIII },
{"glCheckFramebufferStatusOES", "(I)I", (void *) android_glCheckFramebufferStatusOES__I },
{"glDeleteFramebuffersOES", "(I[II)V", (void *) android_glDeleteFramebuffersOES__I_3II },
{"glDeleteFramebuffersOES", "(ILjava/nio/IntBuffer;)V", (void *) android_glDeleteFramebuffersOES__ILjava_nio_IntBuffer_2 },
{"glDeleteRenderbuffersOES", "(I[II)V", (void *) android_glDeleteRenderbuffersOES__I_3II },
{"glDeleteRenderbuffersOES", "(ILjava/nio/IntBuffer;)V", (void *) android_glDeleteRenderbuffersOES__ILjava_nio_IntBuffer_2 },
{"glFramebufferRenderbufferOES", "(IIII)V", (void *) android_glFramebufferRenderbufferOES__IIII },
{"glFramebufferTexture2DOES", "(IIIII)V", (void *) android_glFramebufferTexture2DOES__IIIII },
{"glGenerateMipmapOES", "(I)V", (void *) android_glGenerateMipmapOES__I },
{"glGenFramebuffersOES", "(I[II)V", (void *) android_glGenFramebuffersOES__I_3II },
{"glGenFramebuffersOES", "(ILjava/nio/IntBuffer;)V", (void *) android_glGenFramebuffersOES__ILjava_nio_IntBuffer_2 },
{"glGenRenderbuffersOES", "(I[II)V", (void *) android_glGenRenderbuffersOES__I_3II },
{"glGenRenderbuffersOES", "(ILjava/nio/IntBuffer;)V", (void *) android_glGenRenderbuffersOES__ILjava_nio_IntBuffer_2 },
{"glGetFramebufferAttachmentParameterivOES", "(III[II)V", (void *) android_glGetFramebufferAttachmentParameterivOES__III_3II },
{"glGetFramebufferAttachmentParameterivOES", "(IIILjava/nio/IntBuffer;)V", (void *) android_glGetFramebufferAttachmentParameterivOES__IIILjava_nio_IntBuffer_2 },
{"glGetRenderbufferParameterivOES", "(II[II)V", (void *) android_glGetRenderbufferParameterivOES__II_3II },
{"glGetRenderbufferParameterivOES", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetRenderbufferParameterivOES__IILjava_nio_IntBuffer_2 },
{"glGetTexGenfv", "(II[FI)V", (void *) android_glGetTexGenfv__II_3FI },
{"glGetTexGenfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glGetTexGenfv__IILjava_nio_FloatBuffer_2 },
{"glGetTexGeniv", "(II[II)V", (void *) android_glGetTexGeniv__II_3II },
{"glGetTexGeniv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetTexGeniv__IILjava_nio_IntBuffer_2 },
{"glGetTexGenxv", "(II[II)V", (void *) android_glGetTexGenxv__II_3II },
{"glGetTexGenxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glGetTexGenxv__IILjava_nio_IntBuffer_2 },
{"glIsFramebufferOES", "(I)Z", (void *) android_glIsFramebufferOES__I },
{"glIsRenderbufferOES", "(I)Z", (void *) android_glIsRenderbufferOES__I },
{"glRenderbufferStorageOES", "(IIII)V", (void *) android_glRenderbufferStorageOES__IIII },
{"glTexGenf", "(IIF)V", (void *) android_glTexGenf__IIF },
{"glTexGenfv", "(II[FI)V", (void *) android_glTexGenfv__II_3FI },
{"glTexGenfv", "(IILjava/nio/FloatBuffer;)V", (void *) android_glTexGenfv__IILjava_nio_FloatBuffer_2 },
{"glTexGeni", "(III)V", (void *) android_glTexGeni__III },
{"glTexGeniv", "(II[II)V", (void *) android_glTexGeniv__II_3II },
{"glTexGeniv", "(IILjava/nio/IntBuffer;)V", (void *) android_glTexGeniv__IILjava_nio_IntBuffer_2 },
{"glTexGenx", "(III)V", (void *) android_glTexGenx__III },
{"glTexGenxv", "(II[II)V", (void *) android_glTexGenxv__II_3II },
{"glTexGenxv", "(IILjava/nio/IntBuffer;)V", (void *) android_glTexGenxv__IILjava_nio_IntBuffer_2 },
};

int register_com_google_android_gles_jni_GLImpl(JNIEnv *_env)
{
    int err;
    err = android::AndroidRuntime::registerNativeMethods(_env, classPathName, methods, NELEM(methods));
    return err;
}
