#pragma once

namespace engine {

    template<class T>
    class Singleton {
    public:
        static T* get() {
            static T Instance;
            return &Instance;
        }

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    private:
        Singleton(const Singleton&);              // �R�s�[�R���X�g���N�^�֎~
        Singleton& operator= (const Singleton&);  // ������Z�֎~
        Singleton(Singleton&&);                   // ���[�u�R���X�g���N�^�֎~
        Singleton&& operator= (Singleton&&);      // ���[�u���Z�q�֎~
    };

}