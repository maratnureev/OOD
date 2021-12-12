import {ISignal, Signal} from "../Signal";
import {ShapeType} from "./ShapeType";

class Shape
{
    private readonly m_id: number
    private readonly m_type: ShapeType
    private m_left: number
    private m_width: number
    private m_height: number
    private m_top: number
    private onFrameChanged: ISignal<void> = new Signal<void>()

    constructor (id: number, type: ShapeType, left: number, top: number, width: number, height: number) {
        this.m_width = width;
        this.m_height = height
        this.m_left = left
        this.m_top = top
        this.m_id = id
        this.m_type = type
    }

    getOnFrameChanged() {
        return this.onFrameChanged
    }
    getId() {
        return this.m_id
    }
    getWidth() {
        return this.m_width
    }
    getHeight() {
        return this.m_height
    }
    setFrame(left: number, top: number, width: number, height: number) {
        this.m_left = left;
        this.m_top = top;
        this.m_width = width;
        this.m_height = height;
        this.onFrameChanged.dispatch()
    }
    getLeft() {
        return this.m_left
    }
    getTop() {
        return this.m_top
    }
    getType() {
        return this.m_type
    }
}

export {
    Shape,
}