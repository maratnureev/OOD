import {IEvent, Event} from "../Event";
import {ShapeType} from "./ShapeType";
import {Canvas} from "./Canvas";
import {Frame} from "./Frame";

class Shape
{
    private readonly m_id: string
    private readonly m_type: ShapeType
    private readonly m_canvas: Canvas
    private m_frame: Frame
    private onFrameChanged: IEvent<void> = new Event<void>()

    constructor (id: string, frame: Frame, type: ShapeType, canvas: Canvas) {
        this.m_canvas = canvas
        this.m_frame = frame
        this.m_id = id
        this.m_type = type
    }

    getOnFrameChanged() {
        return this.onFrameChanged
    }

    getId() {
        return this.m_id
    }

    getFrame() {
        return this.m_frame
    }

    setFrame(frame: Frame) {
        this.m_frame = frame
        this.onFrameChanged.dispatch()
    }

    getType() {
        return this.m_type
    }

    getCanvas() {
        return this.m_canvas
    }

    serialize() {
        return {
            id: this.m_id,
            frame: this.m_frame,
            type: this.m_type,
        }
    }
}

type SerializedShape = {
    id: string,
    frame: Frame
    type: ShapeType
}

export {
    Shape
};
export type { SerializedShape };
