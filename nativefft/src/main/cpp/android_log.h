//
// Created by Jaehong Yoo on 2021/10/21.
//

#ifndef FSRFFTLIBRARYAPP_ANDROID_LOG_H
#define FSRFFTLIBRARYAPP_ANDROID_LOG_H

#include <android/log.h>

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "libnav", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "libnav", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "libnav", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "libnav", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "libnav", __VA_ARGS__)

#endif //FSRFFTLIBRARYAPP_ANDROID_LOG_H
