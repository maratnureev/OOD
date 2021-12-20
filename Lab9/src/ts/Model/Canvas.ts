import {ISignal, Signal} from "../Signal";
import {Shape} from "./Shape";

class Canvas {
    private readonly m_width: number
    private readonly m_height: number
    private readonly m_left: number
    private readonly m_top: number
    private m_selectedShapeId: number|null
    private m_shapes: Map<number, Shape> = new Map
    private onSelectedShapeChanged: ISignal<number|null> = new Signal<number|null>()
    private onShapesChanged: ISignal<number> = new Signal<number>()

    constructor (width: number, height: number, left: number, top: number) {
        this.m_left = left
        this.m_top = top
        this.m_width = width
        this.m_height = height
        this.m_selectedShapeId = null
    }

    getOnShapesChanged() {
        return this.onShapesChanged
    }

    getOnSelectedShapeChanged() {
        return this.onSelectedShapeChanged
    }

    getWidth() {
        return this.m_width
    }

    getHeight() {
        return this.m_height
    }

    getLeft() {
        return this.m_left
    }

    getTop() {
        return this.m_top
    }

    addShape(shape: Shape) {
        this.m_shapes.set(shape.getId(), shape)
        this.onShapesChanged.dispatch(shape.getId())
    }

    getShapeById(shapeId: number) {
        return this.m_shapes.get(shapeId)
    }

    selectShape(shapeId: number|null) {
        this.m_selectedShapeId = shapeId
        this.onSelectedShapeChanged.dispatch(shapeId)
    }

    removeShape(shapeId: number) {
        this.m_shapes.delete(shapeId)
        this.onShapesChanged.dispatch(shapeId)
    }

    getSelectedShapeId() {
        return this.m_selectedShapeId
    }
}

export {
    Canvas
}