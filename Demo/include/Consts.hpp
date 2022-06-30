#pragma once

constexpr unsigned FRAMERATE = 60;
constexpr char WINDOW_NAME[] = "Physics Engine";

constexpr int WINDOW_SCALE = 100;
constexpr int WINDOW_WIDTH = 16 * WINDOW_SCALE;
constexpr int WINDOW_HEIGHT = 9 * WINDOW_SCALE;

constexpr float CAM_SCALE = 2.0f;
constexpr float CAM_WIDTH = 16.0f * CAM_SCALE;
constexpr float CAM_HEIGHT = 9.0f * CAM_SCALE;

const sf::View DEFAULT_VIEW(sf::Vector2f(0, 0), sf::Vector2f(CAM_WIDTH, CAM_HEIGHT));