import {Canvas} from "../Model/Canvas";

class SelectionController {
    private m_canvas: Canvas
    constructor(canvas: Canvas) {
        this.m_canvas = canvas
    }

    resizeShape(left: number, top: number, right: number, bottom: number) {
        const selectedShapeId = this.m_canvas.getSelectedShapeId()
        if (selectedShapeId === null) {
            return
        }
        const selectedShape = this.m_canvas.getShapeById(selectedShapeId)
        if (!selectedShape) {
            return
        }
        const frame = selectedShape.getFrame()
        left = Math.min(Math.max(left, 0), frame.left + frame.width)
        top = Math.min(Math.max(top, 0), frame.top + frame.height)
        right = Math.min(Math.max(right, frame.left), this.m_canvas.getWidth())
        bottom = Math.min(Math.max(bottom, frame.top), this.m_canvas.getHeight())
        selectedShape.setFrame({
            left: left,
            top: top,
            width: right - left,
            height: bottom - top,
        })
    }
}

export {
    SelectionController
}