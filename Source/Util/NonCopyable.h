#ifndef OPENGL_BOILERPLATE_NONCOPYABLE_H
#define OPENGL_BOILERPLATE_NONCOPYABLE_H

namespace Util {
    struct NonCopyable {
        NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#endif //OPENGL_BOILERPLATE_NONCOPYABLE_H
