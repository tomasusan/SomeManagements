#pragma once

/**
 * @author tomasusan
 * @date 2025-09-24
 * @brief 单例类
 * @tparam T 单例模板
 */
template<typename T>
class Singleton {
public:
    Singleton() = default;
    Singleton(Singleton const &) = delete;

    Singleton &operator=(Singleton const &) = delete;

    /**
     * @author tomasusan
     * @date 2025-09-24
     * @brief 获取单例
     * @return 返回单例指针
     */
    static T* GetInstance() {
        static T instance;
        return &instance;
    }
};
