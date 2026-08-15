#pragma once

namespace XRay::Engine {
void PreRenderThread();
void PreRenderPostTransformsThread();
void CalculateBonesThread();
void GameThread();
} // namespace XRay::Engine
