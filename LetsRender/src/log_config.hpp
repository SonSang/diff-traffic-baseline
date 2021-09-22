#ifndef LOG_CONFIG_HPP
#define LOG_CONFIG_HPP

#ifdef ANDROID

#include <android/log.h>

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)

#else

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGE(...)  printf(__VA_ARGS__)
#define  LOGV(...)  printf(__VA_ARGS__)

#endif

#endif
