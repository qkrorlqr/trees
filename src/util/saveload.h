#pragma once

#include <iostream>
#include <vector>

namespace NTrees {
    namespace NDebug {
        inline void DebugSave(uint8_t t) {
            std::cout << "saving uint8 " << t << std::endl;
        }

        inline void DebugSave(uint16_t t) {
            std::cout << "saving uint16 " << t << std::endl;
        }

        inline void DebugSave(uint32_t t) {
            std::cout << "saving uint32 " << t << std::endl;
        }

        inline void DebugSave(uint64_t t) {
            std::cout << "saving uint64 " << t << std::endl;
        }

        inline void DebugSave(int8_t t) {
            std::cout << "saving int8 " << t << std::endl;
        }

        inline void DebugSave(int16_t t) {
            std::cout << "saving int16 " << t << std::endl;
        }

        inline void DebugSave(int32_t t) {
            std::cout << "saving int32 " << t << std::endl;
        }

        inline void DebugSave(int64_t t) {
            std::cout << "saving int64 " << t << std::endl;
        }

        inline void DebugSave(float f) {
            std::cout << "saving float " << f << std::endl;
        }

        inline void DebugSave(double f) {
            std::cout << "saving double " << f << std::endl;
        }
    }

    template <class T>
    inline void BinSave(T t, std::ostream& os) {
        //NDebug::DebugSave(t);
        const char* arr = reinterpret_cast<const char*>(&t);
        os.write(arr, sizeof(t));
    }

    template <class T>
    inline void BinLoad(std::istream& is, T* t) {
        is.read(reinterpret_cast<char*>(t), sizeof(*t));
    }

#define SAVELOAD_PRIMITIVE(type)                          \
    inline void Save(type x, std::ostream& os) {          \
	    BinSave(x, os);                                   \
    }                                                     \
    inline void Load(std::istream& is, type* x) {         \
        BinLoad(is, x);                                   \
    }

    SAVELOAD_PRIMITIVE(uint8_t);
    SAVELOAD_PRIMITIVE(uint16_t);
    SAVELOAD_PRIMITIVE(uint32_t);
    SAVELOAD_PRIMITIVE(uint64_t);
    SAVELOAD_PRIMITIVE(int8_t);
    SAVELOAD_PRIMITIVE(int16_t);
    SAVELOAD_PRIMITIVE(int32_t);
    SAVELOAD_PRIMITIVE(int64_t);
    SAVELOAD_PRIMITIVE(float);
    SAVELOAD_PRIMITIVE(double);

#undef SAVELOAD_PRIMITIVE

    template <class T>
    void Save(const std::vector<T>& v, std::ostream& os) {
        Save(v.size(), os);
        for (const auto& x : v) {
            Save(x, os);
        }
    }

    template <class T>
    void Load(std::istream& is, std::vector<T>* v) {
        size_t sz;
        Load(is, &sz);
        v->resize(sz);
        for (size_t i = 0; i < v->size(); ++i) {
            Load(is, &(*v)[i]);
        }
    }
}

