import { Shape } from "../Model/Shape";
import {ShapeView} from "./ShapeView";
import {CanvasView} from "./CanvasView";

class TriangleView extends ShapeView
{
    constructor(model: Shape, parentElement: HTMLElement) {
        super(model, parentElement)
    }
    protected getShapeSVG(): string {
        const model = this.getModel()
        const frame = model.getFrame()
        return `<svg
            xmlns='http://www.w3.org/2000/svg'
            width='100%'
            height='100%'
            viewPort='0 0 ${frame.width} ${frame.height}'>"
            <polygon points='${0},${frame.height} ${frame.width},${frame.height} ${frame.width / 2},${0}' fill='light blue' />
        </svg>`
    }
}

export {
    TriangleView,
}