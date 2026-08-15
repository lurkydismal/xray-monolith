#pragma once

namespace _math_internal {

extern bool g_initialize_cpu_called;

void spline2(float t, Fvector* p, Fvector* ret);
void spline3(float t, Fvector* p, Fvector* ret);

}
