import {Canvas} from "../Model/Canvas";
import { Selection } from "../Model/Selection";
import {Shape} from "../Model/Shape";

class ToolbarController {
    private m_canvas: Canvas

    constructor(canvas: Canvas) {
        this.m_canvas = canvas
    }

    addShape(shape: Shape) {
        this.m_canvas.addShape(shape)
    }

    removeShape(shapeId: string) {
        this.m_canvas.removeShape(shapeId)
    }
}

export {
    ToolbarController
}