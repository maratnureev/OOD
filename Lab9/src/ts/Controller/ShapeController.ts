import {Shape} from "../Model/Shape";
import {ShapeView} from "../View/ShapeView";

class ShapeController
{
    private m_model: Shape;
    private m_view: ShapeView;
    constructor(model: Shape, view: ShapeView) {
        this.m_model = model
        this.m_view = view
    }

    setFrame(left: number, top: number, width: number, height: number) {
        this.m_model.setFrame(left, top, width, height)
    }
}

export {
    ShapeController,
}