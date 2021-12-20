import { Shape } from "../Model/Shape";
import { ShapeView } from "./ShapeView";
import {CanvasView} from "./CanvasView";

class EllipseView extends ShapeView
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
            width='${width}'
            height='${height}'
            viewPort='0 0 ${width} ${height}'>"
            <ellipse rx='${width / 2}' ry='${height / 2}' cx='${width / 2}' cy='${height / 2}' fill="pink" />
        </svg>`
    }
}

export {
    EllipseView,
}