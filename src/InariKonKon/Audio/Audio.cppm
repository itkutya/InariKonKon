module;

#include "miniaudio.h"
//TODO: Steam audio...

export module Audio;

export namespace ikk
{
    void test()
    {
        ma_engine engine;
        if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) return;
        auto res = ma_engine_play_sound(&engine, "sound.wav", nullptr);
        ma_engine_uninit(&engine);
    }
}
