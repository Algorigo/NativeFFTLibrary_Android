//
// Created by Jaehong Yoo on 2021/10/21.
//

#ifndef FSRFFTLIBRARYAPP_JNI_CONVERTER_H
#define FSRFFTLIBRARYAPP_JNI_CONVERTER_H

#include <jni.h>
#include <complex>

using std::complex;

#ifdef __cplusplus
extern "C" {
#endif

jint listToDataArray(JNIEnv *env, jint arrayCount, jobject values, complex<double> **data_in, complex<double> **data_out);
jobject vectorToAbsList(JNIEnv *env, jint arrayCount, jint size, const complex<double> *data_out);
jobject vectorToComplexArrayList(JNIEnv *env, jint arrayCount, jint size, const complex<double> *data_out);
jobject vectorToAbsSumList(JNIEnv *env, jint arrayCount, jint size, const complex<double> *data_out);

#ifdef __cplusplus
}
#endif

#endif //FSRFFTLIBRARYAPP_JNI_CONVERTER_H
