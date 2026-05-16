#include <GE.h>
#include <GE/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace GE {

class GEEditor : public Application {
public:
    GEEditor()
        : Application("Hazel Editor") {
        auto *editorLayer = new EditorLayer();
        PushLayer(editorLayer);
    }

    ~GEEditor() override = default;
};

Application *CreateApplication() {
    return new GEEditor();
}

}