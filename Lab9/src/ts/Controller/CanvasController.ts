import {Canvas} from "../Model/Canvas";
import {CanvasView} from "../View/CanvasView";

class CanvasController
{
    private m_model: Canvas;
    private m_view: CanvasView;
    constructor(model: Canvas, view: CanvasView) {
        this.m_model = model
        this.m_view = view
    }

    selectShape(shapeId: string|null) {
        this.m_model.selectShape(shapeId)
    }
}

export {
    CanvasController,
}