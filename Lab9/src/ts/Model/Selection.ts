import { IEvent, Event } from "../Event"
import { Shape } from "./Shape"

class Selection {
    private m_selectedShape: Shape|null = null
    private onSelectedShapeChanged: IEvent<Shape|null> = new Event()

    getSelectedShape() {
        return this.m_selectedShape
    }

    selectShape(shape: Shape|null) {
        this.m_selectedShape = shape
        this.onSelectedShapeChanged.dispatch(shape)
    }

    getOnSelectedShapeChanged() {
        return this.onSelectedShapeChanged
    }
}

export {
    Selection
}