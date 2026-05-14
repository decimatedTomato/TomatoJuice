#pragma once
/**
 * How to control levels of asserts?
 * Should there be a project wide define or different functions which handle failure differently.
 * Should it depend on DEBUG being defined?
 * It definitely shouldn't be a runtime controllable thing.
 * Either it crashes or its unreachable code.
 */

#include <assert.h>
#define TOMATO_ASSERT assert
