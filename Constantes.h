#pragma once

/**
 * Math constants shared by every fractal program.
 *
 * M_PI is not part of standard C++, and the Windows headers only expose it when
 * _USE_MATH_DEFINES is set, so each program used to define it for itself. The
 * guard keeps the definition harmless if the platform headers provide it first.
 */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
