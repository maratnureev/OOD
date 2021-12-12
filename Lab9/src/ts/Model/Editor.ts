import {ISignal, Signal} from "../Signal";
import {Shape} from "./Shape";

class Editor {
    private readonly m_width: number
    private readonly m_height: number
    private onShapesChanged: ISignal<number> = new Signal<number>()
    private m_shapes: Map<number, Shape> = new Map

    constructor (width: number, height: number) {
        this.m_width = width;
        this.m_height = height;
    }

    getOnShapesChanged() {
        return this.onShapesChanged
    }

    getWidth() {
        return this.m_width
    }

    getHeight() {
        return this.m_height
    }

    addShape(shape: Shape) {
        this.m_shapes.set(shape.getId(), shape)
        this.onShapesChanged.dispatch(shape.getId())
    }

    getShapeById(shapeId: number) {
        return this.m_shapes.get(shapeId)
    }

    removeShape(shapeId: number) {
        this.m_shapes.delete(shapeId)
        this.onShapesChanged.dispatch(shapeId)
    }
}

export {
    Editor
}