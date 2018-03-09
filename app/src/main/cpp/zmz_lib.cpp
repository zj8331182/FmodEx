#include <jni.h>
#include <string>
#include "com_zmz_fmodex_VoliUtil.h"
#include <fmod.hpp>
#include <unistd.h>

using namespace FMOD;

#define MODE_NORMAL 0
#define MODE_OTHER 1
#define MODE_SECOND 2

System *system;
Sound *sound;

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_zmz_fmodex_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    system->close();
    system->release();
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zmz_fmodex_VoliUtil_fix(JNIEnv *env, jclass type, jstring path_, jint mode) {
    const char *path = env->GetStringUTFChars(path_, 0);

    Channel *channel = NULL;
    DSP *dsp;
    bool isPlaying = true;
    System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, 0);

    system->createSound(path, FMOD_CREATESTREAM, 0, &sound);
    //播放 : 异步
    switch (mode) {
        case MODE_NORMAL:
            system->playSound(sound, 0, false, &channel);
            break;
        case MODE_OTHER:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            //修改值
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8f);
            system->playSound(sound, 0, false, &channel);
            //添加音效
            channel->addDSP(0, dsp);
            break;
        case MODE_SECOND:
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            //修改值
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
            system->playSound(sound, 0, false, &channel);
            //添加音效
            channel->addDSP(0, dsp);
            break;
        default:
            break;
    }

    system->update();

    //检查是否播放完成
    while (isPlaying) {
        channel->isPlaying(&isPlaying);
        sleep(10);
    }

    //释放
    sound->release();
    system->close();
    system->release();

    env->ReleaseStringUTFChars(path_, path);
}extern "C"
JNIEXPORT void JNICALL
Java_com_zmz_fmodex_VoliUtil_stop(JNIEnv *env, jclass type) {
    sound->release();
    system->close();
    system->release();
}