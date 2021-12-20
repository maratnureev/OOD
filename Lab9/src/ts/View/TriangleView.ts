import { Shape } from "../Model/Shape";
import {ShapeView} from "./ShapeView";
import {CanvasView} from "./CanvasView";

class TriangleView extends ShapeView
{
    constructor(model: Shape, canvas: CanvasView) {
        super(model, canvas)
    }
    getShapeHtmlImpl(): string {
        const model = this.getModel()
        const width = model.getWidth()
        const height = model.getHeight()
        return `<svg
            xmlns='http://www.w3.org/2000/svg'
            width='100%'
            height='100%'
            viewPort='0 0 ${width} ${height}'>"
            <polygon points='${0},${height} ${width},${height} ${width / 2},${0}' fill='light blue' />
        </svg>`
    }
}

export {
    TriangleView,
}