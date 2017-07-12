#include "edu_jxfn_jxfn_jni_test.h"


JNIEXPORT jstring JNICALL Java_edu_jxfn_jxfn_jni_1test_JniHelloWorld(
    JNIEnv *env, jobject thiz)
{
    return env->NewStringUTF("Hello from JNI!");
}
