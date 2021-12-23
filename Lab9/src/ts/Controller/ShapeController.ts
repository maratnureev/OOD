import {Shape} from "../Model/Shape";
import {ShapeView} from "../View/ShapeView";
import {Canvas} from "../Model/Canvas";

class ShapeController
{
    private m_shapeModel: Shape;
    constructor(shapeModel: Shape) {
        this.m_shapeModel = shapeModel
    }

    moveShape(left: number, top: number) {
        const canvas = this.m_shapeModel.getCanvas()
        const shapeFrame = this.m_shapeModel.getFrame()
        left = Math.min(Math.max(left, 0), canvas.getWidth() - shapeFrame.width)
        top = Math.min(Math.max(top, 0), canvas.getHeight() - shapeFrame.height)
        this.m_shapeModel.setFrame({
            left,
            top,
            width: shapeFrame.width,
            height: shapeFrame.height
        })
    }
}

export {
    ShapeController,
}