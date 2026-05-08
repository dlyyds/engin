#include <GE.h>
#include <GE/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace GE {

class GEEditor : public Application {
public:
    GEEditor()
        : Application("Hazel Editor") {
        PushLayer(new EditorLayer());
    }

    ~GEEditor() {
    }
};

Application *CreateApplication() {
    return new GEEditor();
}

}