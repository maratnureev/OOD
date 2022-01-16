import {IEvent, Event} from "../Event";
import {Shape} from "./Shape";

class Canvas {
    private readonly m_width: number
    private readonly m_height: number
    private m_shapes: Map<string, Shape> = new Map
    private onShapeAdded: IEvent<string> = new Event<string>()
    private onShapeRemoved: IEvent<string> = new Event<string>()

    constructor (width: number, height: number) {
        this.m_width = width
        this.m_height = height
    }

    getOnShapeAdded() {
        return this.onShapeAdded
    }

    getOnShapeRemoved() {
        return this.onShapeRemoved
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

    removeShape(shapeId: string) {
        this.m_shapes.delete(shapeId)
        this.onShapeRemoved.dispatch(shapeId)
    }

    getShapeIds() {
        return Array.from(this.m_shapes.keys())
    }

    getShapes() {
        return Array.from(this.m_shapes.values())
    }
}

export {
    Canvas
};