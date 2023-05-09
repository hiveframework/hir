/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <cstddef>
#include <cstdint>

#include <fmt/core.h>
#include <fmt/color.h>

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using size = size_t;

#define Log(msg) fmt::print("[LOG] {}\n",   msg);
#define LogRaw(msg) fmt::print("[LOG] {} ", msg);
#define Warn(msg) fmt::print("[WARN] {}\n", msg);
#define Panic(msg) fmt::print("[PANIC] {}:{}\n{}\n",__FILE__, __LINE__, fmt::format(fg(fmt::color::red), msg)); std::exit(-1);

#define For(iterable) for (auto& it : iterable)

#ifdef DEBUG
#define Assert(expression, msg)                                                                         \
	if ((expression)) {                                                                                   \
		fmt::print("assert in file {}:{}\n{}\n",__FILE__, __LINE__,fmt::format(fg(fmt::color::red), msg));  \
		std::exit(-1);                                                                                      \
	}

#define DebugInfo(msg) fmt::print("[DEBUG] {}\n", msg);
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define OS_WINDOWS 1
#elif defined(__linux__) || defined(__gnu_linux__) //damn it RMS
#define OS_LINUX 1
#elif defined(__APPLE__)
#define OS_APPLE 1
#else
#error "Unsupported platform"
#endif
