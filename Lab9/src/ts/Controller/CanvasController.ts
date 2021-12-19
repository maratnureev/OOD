import {Canvas} from "../Model/Canvas";
import {CanvasView} from "../View/CanvasView";
import {Shape} from "../Model/Shape";

class CanvasController
{
    private m_model: Canvas;
    private m_view: CanvasView;
    constructor(model: Canvas, view: CanvasView) {
        this.m_model = model
        this.m_view = view
    }

    addShape(shape: Shape) {
        this.m_model.addShape(shape)
    }

    removeShape(shapeId: number) {
        this.m_model.removeShape(shapeId)
    }

    selectShape(shapeId: number|null) {
        this.m_model.selectShape(shapeId)
    }
}

export {
    CanvasController,
}