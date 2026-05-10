#pragma once

#include "Entity.h"

namespace GE {

class ScriptableEntity {
public:
    virtual ~ScriptableEntity() = default;

    template <typename T>
    T &GetComponent() {
        return m_Entity.GetComponent<T>();
    }

private:
    Entity m_Entity;
    friend class Scene;
};

}

