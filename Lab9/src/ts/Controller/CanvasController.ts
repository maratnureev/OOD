import { Selection } from "../Model/Selection";
import { Shape } from "../Model/Shape";

class CanvasController
{
    private m_selection: Selection;
    constructor(selection: Selection) {
        this.m_selection = selection
    }

    selectShape(shape: Shape|null) {
        this.m_selection.selectShape(shape)
    }
}

export {
    CanvasController,
}