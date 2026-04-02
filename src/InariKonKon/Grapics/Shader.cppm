module;

#include <string_view>
#include <filesystem>
#include <cstdint>
#include <vector>
#include <string>

#include "shaderc/shaderc.hpp"

export module Shader;

import Log;

export namespace ikk
{
    namespace Shader
    {
        enum struct Type : std::uint8_t
        {
            Vertex = 0,
            Fragment,
            Geometry,
            Tessellation,
            Compute,
            Primitive,
            Mesh,
            RayTracing,
            Tensor,
            Undefined
        };
    }

    template<Shader::Type type>
    class BasicShader final
    {
    public:
        explicit BasicShader(std::filesystem::path path) noexcept;
        explicit BasicShader(std::string_view src) noexcept;

        BasicShader(const BasicShader&) noexcept = default;
        BasicShader(BasicShader&&) noexcept = default;

        BasicShader& operator=(const BasicShader&) noexcept = default;
        BasicShader& operator=(BasicShader&&) noexcept = default;

        ~BasicShader() noexcept = default;

        [[nodiscard]] std::vector<std::uint32_t> convertToSPIRV() const noexcept;
    private:
        Shader::Type m_type = type;
        std::filesystem::path m_path = "";
        std::string m_source = {};
    };

    using VertexShader = BasicShader<Shader::Type::Vertex>;
    using FragmentShader = BasicShader<Shader::Type::Fragment>;
}

namespace ikk
{
    //TODO:
    template <Shader::Type type>
    BasicShader<type>::BasicShader(std::filesystem::path path) noexcept
        : m_path(std::move(path))
    {
    }

    template <Shader::Type type>
    BasicShader<type>::BasicShader(std::string_view src) noexcept
        : m_source(src)
    {
    }

    template <Shader::Type type>
    std::vector<std::uint32_t> BasicShader<type>::convertToSPIRV() const noexcept
    {
        const shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
        options.SetOptimizationLevel(shaderc_optimization_level_performance);

        shaderc_shader_kind kind = shaderc_glsl_vertex_shader;
        switch (type)
        {
        case Shader::Type::Vertex: kind = shaderc_glsl_vertex_shader; break;
        case Shader::Type::Fragment: kind = shaderc_glsl_fragment_shader; break;
        default: return {};
        }

        const shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(this->m_source, kind, this->m_path.string().c_str(), options);
        if (module.GetCompilationStatus() != shaderc_compilation_status_success)
            Print<Log::Level::Error>("{}", module.GetErrorMessage());

        return std::vector<std::uint32_t>{ module.cbegin(), module.cend() };
    }
}
