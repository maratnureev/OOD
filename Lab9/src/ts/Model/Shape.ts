import {IEvent, Event} from "../Event";
import {ShapeType} from "./ShapeType";
import {Canvas} from "./Canvas";

class Shape
{
    private readonly m_id: number
    private readonly m_type: ShapeType
    private m_left: number
    private m_width: number
    private m_height: number
    private m_top: number
    private m_canvas: Canvas
    private onFrameChanged: IEvent<void> = new Event<void>()

    constructor (id: number, type: ShapeType, left: number, top: number, width: number, height: number, canvas: Canvas) {
        this.m_canvas = canvas
        this.m_width = width
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

    // этой логике здесь не место. Вынести параметры во Frame 
    setFrame(left: number, top: number, width: number, height: number) {
        const right = Math.min(Math.max(left + width, width), this.m_canvas.getWidth())
        const bottom = Math.min(Math.max(top + height, height), this.m_canvas.getHeight())
        left = Math.min(Math.max(left, 0), this.m_canvas.getWidth() - this.m_width)
        top = Math.min(Math.max(top, 0), this.m_canvas.getHeight() - this.m_height)
        this.m_left = Math.min(left, this.m_left + this.m_width)
        this.m_top = Math.min(top, this.m_top + this.m_height)
        this.m_width = Math.max(right - left, 0)
        this.m_height = Math.max(bottom - top, 0)
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