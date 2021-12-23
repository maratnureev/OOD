import { Shape } from "../Model/Shape";
import { ShapeView} from "./ShapeView";
import {CanvasView} from "./CanvasView";

class RectangleView extends ShapeView
{
    constructor(model: Shape, parentElement: HTMLElement) {
        super(model, parentElement)
    }
    protected getShapeSVG(): string {
        const model = this.getModel()
        const frame = model.getFrame()
        return `<svg
            xmlns='http://www.w3.org/2000/svg'
            width='${frame.width}'
            height='${frame.height}'
            viewPort='0 0 ${frame.width} ${frame.height}'>"
            <polygon points='${0},${0} ${frame.width},${0} ${frame.width},${frame.height} ${0},${frame.height}' fill='brown' />
        </svg>`
    }
}

export {
    RectangleView,
}