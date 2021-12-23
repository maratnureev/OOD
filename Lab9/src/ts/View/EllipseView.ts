import { Shape } from "../Model/Shape";
import { ShapeView } from "./ShapeView";

class EllipseView extends ShapeView
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
            <ellipse rx='${frame.width / 2}' ry='${frame.height / 2}' cx='${frame.width / 2}' cy='${frame.height / 2}' fill="pink" />
        </svg>`
    }
}

export {
    EllipseView,
}