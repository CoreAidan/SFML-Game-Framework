#pragma once

#include "NonCopyable.h"

struct NonMoveable
{
	NonMoveable() = default;
	NonMoveable& operator = (NonCopyable&&) = delete;
	NonMoveable(NonCopyable&&) = delete;
};