/*
 * Copyright 2018 Wultra s.r.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if !defined(ANDROID)
#error "Available only for Android platform"
#endif

#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "wultra_pass_meter.h"


extern "C" {
	
// Java package : com.wultra.android.passphrasemeter
// Java class   : PasswordTester

enum class TestScenario {
    PASSWORD, PASSCODE
};

JNIEXPORT jboolean JNICALL Java_com_wultra_android_passphrasemeter_PasswordTester_loadDictionary(JNIEnv *jenv, jobject self, jobject manager, jstring dictionaryAsset)
{
    bool result = false;
    if (dictionaryAsset != NULL &&  manager != NULL) {
        // Get CPP objects from parameters
        AAssetManager * cppManager = AAssetManager_fromJava(jenv, manager);
        const char *cppDictionaryAsset = jenv->GetStringUTFChars(dictionaryAsset, JNI_FALSE);
        if (cppDictionaryAsset != NULL && cppManager != NULL) {
            // Load dictionary
            result = WPM_setPasswordDictionary(cppManager, cppDictionaryAsset);
            jenv->ReleaseStringUTFChars(dictionaryAsset, cppDictionaryAsset);
        }
    }
    return (jboolean) result;
}

JNIEXPORT void JNICALL Java_com_wultra_android_passphrasemeter_PasswordTester_freeLoadedDictionary(JNIEnv *jenv, jobject self)
{
    WPM_freePasswordDictionary();
}

JNIEXPORT jboolean JNICALL Java_com_wultra_android_passphrasemeter_PasswordTester_hasLoadedDictionary(JNIEnv *jenv, jobject self)
{
    return (jboolean) WPM_hasPasswordDictionary();
}

void test_value(JNIEnv *jenv, TestScenario test_scenario, jint& result, jbyteArray array) {
    jsize arr_length = jenv->GetArrayLength(array);
    jboolean isCopyFlag;
    char* value_original = (char*) jenv->GetByteArrayElements(array, &isCopyFlag);

    if (value_original != NULL) {
        char* value_to_test = (char*) calloc(arr_length + 1, 1);
        memcpy(value_to_test, value_original, arr_length);

        if (isCopyFlag) {
            // clean-up copy - just to be sure
            memset(value_original, 0, arr_length);
        }
        jenv->ReleaseByteArrayElements(array, (jbyte *) value_original, JNI_ABORT);

        switch (test_scenario) {
            case TestScenario::PASSCODE:{
                result = WPM_testPasscode(value_to_test);
            }
            break;
            case TestScenario::PASSWORD:{
                result = WPM_testPassword(value_to_test);
            }
            break;
        }

        // clean-up
        memset(value_to_test, 0, arr_length);
        free(value_to_test);
    }
}

JNIEXPORT jint JNICALL Java_com_wultra_android_passphrasemeter_PasswordTester_testPasswordByteJNI(JNIEnv *jenv, jobject self,
                                                                                                  jbyteArray array)
{
    jint result = WPM_PasswordResult_WrongInput;
    test_value(jenv, TestScenario::PASSWORD, result, array);
    return result;
}

JNIEXPORT jint JNICALL Java_com_wultra_android_passphrasemeter_PasswordTester_testPinByteJNI(JNIEnv *jenv, jobject self,
                                                                                             jbyteArray array)
{
    jint result = WPM_PasscodeResult_WrongInput;
    test_value(jenv, TestScenario::PASSCODE, result, array);
    return result;
}

} // extern "C"
