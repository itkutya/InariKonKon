module;

#include <filesystem>
#include <vector>

#include "miniaudio.h"
#include "phonon.h"

export module Audio;

import Resource;

import Print;

export namespace ikk
{
    class [[nodiscard]] Audio final : public Resource
    {
    public:
        [[nodiscard]] Audio() noexcept;
        [[nodiscard]] explicit Audio(const std::filesystem::path& path) noexcept;

        Audio(const Audio&) noexcept = default;
        Audio(Audio&&) noexcept = default;

        Audio& operator=(const Audio&) noexcept = default;
        Audio& operator=(Audio&&) noexcept = default;

        ~Audio() noexcept;

        virtual void loadFromFile(const std::filesystem::path& path) noexcept override;

        void play() noexcept;
        void pause() noexcept;
        void stop() noexcept;
    private:
        ma_engine m_engine{};
        ma_sound m_sound{};

        //TODO: Instead...
        std::vector<float> m_data{};
    };

    Audio::Audio() noexcept
    {
        if (const auto result = ma_engine_init(nullptr, &this->m_engine); result != MA_SUCCESS)
        {
            Print<Log::Level::Error>("Error: {}", ma_result_description(result));
            return;
        }
    }

    Audio::Audio(const std::filesystem::path& path) noexcept
    {
        if (const auto result = ma_engine_init(nullptr, &this->m_engine); result != MA_SUCCESS)
        {
            Print<Log::Level::Error>("Error: {}", ma_result_description(result));
            return;
        }
        this->loadFromFile(path);
    }

    Audio::~Audio() noexcept
    {
        ma_sound_uninit(&this->m_sound);
        ma_engine_uninit(&this->m_engine);
    }

    void Audio::loadFromFile(const std::filesystem::path& path) noexcept
    {
        const auto result = ma_sound_init_from_file(
            &this->m_engine,
            path.string().c_str(),
            MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC | MA_SOUND_FLAG_STREAM,
            nullptr,
            nullptr,
            &this->m_sound);

        if (result != MA_SUCCESS)
            Print<Log::Level::Error>("Error: {}, with file: {}", ma_result_description(result), path);
    }

    void Audio::play() noexcept
    {
        if (const auto result = ma_sound_start(&this->m_sound); result != MA_SUCCESS)
            Print<Log::Level::Error>("Error: {}", ma_result_description(result));
    }

    void Audio::pause() noexcept
    {
        //TODO:
    }

    void Audio::stop() noexcept
    {
        ma_sound_stop(&this->m_sound);
    }
}
