import { Shape } from "../Model/Shape";
import { ShapeView} from "./ShapeView";
import {CanvasView} from "./CanvasView";

class RectangleView extends ShapeView
{
    constructor(model: Shape, canvas: CanvasView) {
        super(model, canvas)
    }
    getShapeSVG(): string {
        const model = this.getModel()
        const width = model.getWidth()
        const height = model.getHeight()
        return `<svg
            xmlns='http://www.w3.org/2000/svg'
            width='${width}'
            height='${height}'
            viewPort='0 0 ${width} ${height}'>"
            <polygon points='${0},${0} ${width},${0} ${width},${height} ${0},${height}' fill='brown' />
        </svg>`
    }
}

export {
    RectangleView,
}