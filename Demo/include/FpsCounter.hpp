#pragma once

#include <sstream>
#include <string>

class FpsCounter
{
public:
    [[nodiscard]] float GetFps() const;
    [[nodiscard]] std::string GetFpsString() const;
    void Update(float deltaTime);
private:
    int _frameCount{};
    float _fps{};
    float _accumulator = 0;
};

inline void FpsCounter::Update(const float deltaTime)
{
    // Time in seconds when the fps counter should update
    constexpr float timeToUpdate = 0.7f;

    _frameCount++;
    _accumulator += deltaTime;

    if (_accumulator >= timeToUpdate)
    {
        _accumulator -= timeToUpdate;
        _fps = static_cast<float>(_frameCount) / timeToUpdate;
        _frameCount = 0;
    }
}

inline float FpsCounter::GetFps() const
{
    return _fps;
}

inline std::string FpsCounter::GetFpsString() const
{
    std::ostringstream oss{};
    oss << GetFps();
    return oss.str();
}
