import {IEvent, Event} from "../Event";
import {SerializedShape, Shape} from "./Shape";

class Canvas {
    private readonly m_width: number
    private readonly m_height: number
    private m_selectedShapeId: string|null
    private m_shapes: Map<string, Shape> = new Map
    private onSelectedShapeChanged: IEvent<string|null> = new Event<string|null>()
    private onShapeAdded: IEvent<string> = new Event<string>()
    private onShapeRemoved: IEvent<string> = new Event<string>()

    constructor (width: number, height: number) {
        this.m_width = width
        this.m_height = height
        this.m_selectedShapeId = null
    }

    getOnShapeAdded() {
        return this.onShapeAdded
    }

    getOnShapeRemoved() {
        return this.onShapeRemoved
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

    addShape(shape: Shape) {
        this.m_shapes.set(shape.getId(), shape)
        this.onShapeAdded.dispatch(shape.getId())
    }

    getShapeById(shapeId: string) {
        return this.m_shapes.get(shapeId)
    }

    selectShape(shapeId: string|null) {
        this.m_selectedShapeId = shapeId
        this.onSelectedShapeChanged.dispatch(shapeId)
    }

    removeShape(shapeId: string) {
        this.m_shapes.delete(shapeId)
        this.onShapeRemoved.dispatch(shapeId)
    }

    getSelectedShapeId() {
        return this.m_selectedShapeId
    }

    getShapeIds() {
        return Array.from(this.m_shapes.keys())
    }

    getShapes() {
        return Array.from(this.m_shapes.values())
    }

    serialize() {
        return {
            width: this.m_width,
            height: this.m_height,
            shapes: this.getShapes().map(shape => shape.serialize()),
        }
    }
}

type SerializedCanvas = {
    width: number
    height: number
    shapes: SerializedShape[]
}

export {
    Canvas
};
export type { SerializedCanvas };
