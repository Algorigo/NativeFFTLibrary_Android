//
// Created by Jaehong Yoo on 2021/10/21.
//

#include "jni_converter.h"
#include "android_log.h"

jint listToDataArray(JNIEnv *env, jint arrayCount, jobject values, complex<double> **data_in, complex<double> **data_out, jint n) {
    jclass jclassList = env->GetObjectClass(values);
    jmethodID jmethodIdSize = env->GetMethodID(jclassList, "size", "()I");
    jmethodID jmethodIdGet = env->GetMethodID(jclassList, "get", "(I)Ljava/lang/Object;");
    auto size = env->CallIntMethod(values, jmethodIdSize);
    auto dataSize = n * arrayCount;
    *data_in = new complex<double>[dataSize];
    *data_out = new complex<double>[dataSize];
    fill_n(*data_in, dataSize, complex<double>(0.));
    for (auto index=0; index<size; index++) {
        jdoubleArray jdoubles = (jdoubleArray)env->CallObjectMethod(values, jmethodIdGet, index);
        auto doubleArraySize = env->GetArrayLength(jdoubles);
        auto doubles = env->GetDoubleArrayElements(jdoubles, NULL);
        for (auto arrayIdx=0; arrayIdx<doubleArraySize; arrayIdx++) {
            auto doubleValue = doubles[arrayIdx];
            (*data_in)[index+arrayIdx*n] = complex<double>(doubleValue);
        }
        env->ReleaseDoubleArrayElements(jdoubles, doubles, JNI_ABORT);
        env->DeleteLocalRef(jdoubles);
    }
    env->DeleteLocalRef(jclassList);
    return n;
}

jobject vectorToComplexArrayList(JNIEnv *env, jint arrayCount, jint size, const complex<double> *data_out) {
    jclass jclassArrayList = env->FindClass("java/util/ArrayList");
    jmethodID jmethodIdListConstructor = env->GetMethodID(jclassArrayList, "<init>", "()V");
    jmethodID jmethodIdAdd = env->GetMethodID(jclassArrayList, "add", "(Ljava/lang/Object;)Z");
    jclass jclassComplex = env->FindClass("com/algorigo/nativefft/Complex");
    jmethodID jmethodIdComplexConstructor = env->GetMethodID(jclassComplex, "<init>","(DD)V");
    jobject resultList = env->NewObject(jclassArrayList, jmethodIdListConstructor);
    for (auto index=0; index<size; index++) {
        jobjectArray resultArray = env->NewObjectArray(arrayCount, jclassComplex, NULL);
        for (auto arrayIdx=0; arrayIdx<arrayCount; arrayIdx++) {
            auto complexValue = data_out[index+arrayIdx*size];
            jobject jcomplex = env->NewObject(jclassComplex, jmethodIdComplexConstructor, complexValue.real(), complexValue.imag());
            env->SetObjectArrayElement(resultArray, arrayIdx, jcomplex);
            env->DeleteLocalRef(jcomplex);
        }
        env->CallBooleanMethod(resultList, jmethodIdAdd, resultArray);
        env->DeleteLocalRef(resultArray);
    }
    env->DeleteLocalRef(jclassComplex);
    env->DeleteLocalRef(jclassArrayList);
    return resultList;
}

jobject vectorToAbsList(JNIEnv *env, jint arrayCount, jint size, const complex<double> *data_out) {
    jclass jclassArrayList = env->FindClass("java/util/ArrayList");
    jmethodID jmethodIdListConstructor = env->GetMethodID(jclassArrayList, "<init>", "()V");
    jmethodID jmethodIdAdd = env->GetMethodID(jclassArrayList, "add", "(Ljava/lang/Object;)Z");
    jobject resultList = env->NewObject(jclassArrayList, jmethodIdListConstructor);
    for (auto index=0; index<size; index++) {
        jdoubleArray resultArray = env->NewDoubleArray(arrayCount);
        double results[arrayCount];
        for (auto arrayIdx=0; arrayIdx<arrayCount; arrayIdx++) {
            auto complexValue = data_out[index+arrayIdx*size];
            auto abs = sqrt(pow(complexValue.real(), 2)+pow(complexValue.imag(), 2));
            results[arrayIdx] = abs;
        }
        env->SetDoubleArrayRegion(resultArray, 0, arrayCount, results);
        env->CallBooleanMethod(resultList, jmethodIdAdd, resultArray);
        env->DeleteLocalRef(resultArray);
    }
    env->DeleteLocalRef(jclassArrayList);
    return resultList;
}

jobject vectorToAbsSumList(JNIEnv *env, jint arrayCount, jint size, const complex<double> *data_out) {
    jclass jclassArrayList = env->FindClass("java/util/ArrayList");
    jmethodID jmethodIdListConstructor = env->GetMethodID(jclassArrayList, "<init>", "()V");
    jmethodID jmethodIdAdd = env->GetMethodID(jclassArrayList, "add", "(Ljava/lang/Object;)Z");
    jclass jclassDouble = env->FindClass("java/lang/Double");
    jmethodID jmethodIdDoubleConstructor = env->GetMethodID(jclassDouble, "<init>", "(D)V");
    jobject resultList = env->NewObject(jclassArrayList, jmethodIdListConstructor);
    for (auto index=0; index<size; index++) {
        double results = 0.;
        for (auto arrayIdx=0; arrayIdx<arrayCount; arrayIdx++) {
            auto complexValue = data_out[index+arrayIdx*size];
            auto abs = sqrt(pow(complexValue.real(), 2)+pow(complexValue.imag(), 2));
            results += abs;
        }
        jobject jobjectDouble = env->NewObject(jclassDouble, jmethodIdDoubleConstructor, results);
        env->CallBooleanMethod(resultList, jmethodIdAdd, jobjectDouble);
        env->DeleteLocalRef(jobjectDouble);
    }
    env->DeleteLocalRef(jclassArrayList);
    return resultList;
}
