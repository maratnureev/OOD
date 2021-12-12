import {Editor} from "../Model/Editor";
import {EditorView} from "../View/EditorView";
import {Shape} from "../Model/Shape";

class EditorController
{
    private m_model: Editor;
    private m_view: EditorView;
    constructor(model: Editor, view: EditorView) {
        this.m_model = model
        this.m_view = view
    }

    addShape(shape: Shape) {
        this.m_model.addShape(shape)
    }

    removeShape(shapeId: number) {
        this.m_model.removeShape(shapeId)
    }
}

export {
    EditorController,
}