#include <jni.h>
#include <string>
#include <chrono>
#include <typeinfo>
#include "android_log.h"
#include "jni_converter.h"
#include "pocketfft-cpp/pocketfft_hdronly.h"

using namespace std::chrono;
using std::size_t;
using std::ptrdiff_t;
using std::complex;
using pocketfft::shape_t;
using pocketfft::stride_t;

inline long getCurrentMillis() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_algorigo_nativefft_NativeFFT_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_algorigo_nativefft_NativeFFT_fftC2c(
        JNIEnv* env,
        jclass /* class */,
        jint arrayCount,
        jobject values) {

    auto durationMillis = getCurrentMillis();

    complex<double> *data_in;
    complex<double> *data_out;
    jint size = listToDataArray(env, arrayCount, values, &data_in, &data_out);

    shape_t shape_in(2);
    shape_in[0] = size;
    shape_in[1] = arrayCount;
    stride_t stride_in(2);
    stride_in[0] = sizeof(complex<double>);
    stride_in[1] = stride_in[0] * size;

    stride_t stride_out(2);
    stride_out[0] = sizeof(complex<double>);
    stride_out[1] = stride_out[0] * size;

    shape_t axis(1);
    axis[0] = 0;
    bool forward = true;
    double fct = 1.;

    pocketfft::c2c<double>(shape_in, stride_in, stride_out, axis, forward, data_in, data_out, fct);

    jobject resultList = vectorToComplexArrayList(env, arrayCount, size, data_out);

    durationMillis = getCurrentMillis() - durationMillis;
    LOGE("duration : %ld ms", durationMillis);

    delete[] data_in;
    delete[] data_out;

    return resultList;
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_algorigo_nativefft_NativeFFT_fftC2cAbs(
        JNIEnv* env,
        jclass /* class */,
        jint arrayCount,
        jobject values) {

    auto durationMillis = getCurrentMillis();

    complex<double> *data_in;
    complex<double> *data_out;
    jint size = listToDataArray(env, arrayCount, values, &data_in, &data_out);

    shape_t shape_in(2);
    shape_in[0] = size;
    shape_in[1] = arrayCount;
    stride_t stride_in(2);
    stride_in[0] = sizeof(complex<double>);
    stride_in[1] = stride_in[0] * size;

    stride_t stride_out(2);
    stride_out[0] = sizeof(complex<double>);
    stride_out[1] = stride_out[0] * size;

    shape_t axis(1);
    axis[0] = 0;
    bool forward = true;
    double fct = 1.;

    pocketfft::c2c<double>(shape_in, stride_in, stride_out, axis, forward, data_in, data_out, fct);

    jobject resultList = vectorToAbsList(env, arrayCount, size, data_out);

    durationMillis = getCurrentMillis() - durationMillis;
    LOGE("duration : %ld ms", durationMillis);

    delete[] data_in;
    delete[] data_out;

    return resultList;
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_algorigo_nativefft_NativeFFT_fftC2cAbsSum(
        JNIEnv* env,
        jclass /* class */,
        jint arrayCount,
        jobject values) {

    auto durationMillis = getCurrentMillis();

    complex<double> *data_in;
    complex<double> *data_out;
    jint size = listToDataArray(env, arrayCount, values, &data_in, &data_out);

    shape_t shape_in(2);
    shape_in[0] = size;
    shape_in[1] = arrayCount;
    stride_t stride_in(2);
    stride_in[0] = sizeof(complex<double>);
    stride_in[1] = stride_in[0] * size;

    stride_t stride_out(2);
    stride_out[0] = sizeof(complex<double>);
    stride_out[1] = stride_out[0] * size;

    shape_t axis(1);
    axis[0] = 0;
    bool forward = true;
    double fct = 1.;

    pocketfft::c2c<double>(shape_in, stride_in, stride_out, axis, forward, data_in, data_out, fct);

    jobject resultList = vectorToAbsSumList(env, arrayCount, size, data_out);

    durationMillis = getCurrentMillis() - durationMillis;
    LOGE("duration : %ld ms", durationMillis);

    delete[] data_in;
    delete[] data_out;

    return resultList;
}

extern "C" JNIEXPORT void JNICALL
Java_com_algorigo_nativefft_NativeFFT_test(
        JNIEnv *env,
        jclass /* class */) {
    LOGE("test print");
}