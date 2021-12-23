import {Canvas} from "../Model/Canvas";
import {Shape} from "../Model/Shape";

class ToolbarController {
    private m_model: Canvas;
    constructor(model: Canvas) {
        this.m_model = model
    }

    addShape(shape: Shape) {
        this.m_model.addShape(shape)
    }

    removeShape(shapeId: string) {
        this.m_model.removeShape(shapeId)
    }

    selectShape(shapeId: string|null) {
        this.m_model.selectShape(shapeId)
    }
}

export {
    ToolbarController
}