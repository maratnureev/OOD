import {ResizeHandler} from "./ResizeHandler";
import {ShapeView} from "./ShapeView";
import {CanvasView} from "./CanvasView";
import {Shape} from "../Model/Shape";

class SelectionView {
    private readonly m_element: HTMLElement
    private m_onFrameChangeUnsubscribe: (() => void)|null = null
    private m_resizeHandler: ResizeHandler
    private m_canvas: CanvasView

    constructor(canvas: CanvasView) {
        this.m_element = document.createElement('div')
        this.m_element.style.boxShadow = '0 0 0 1px black'
        this.m_element.style.position = 'absolute'
        this.m_element.style.pointerEvents = 'none'
        this.m_canvas = canvas
        this.m_resizeHandler = new ResizeHandler(canvas, this.m_element)
    }

    removeSelection() {
        if (this.m_onFrameChangeUnsubscribe !== null) {
            this.m_onFrameChangeUnsubscribe()
            this.m_onFrameChangeUnsubscribe = null
            this.m_canvas.getDOMElement().removeChild(this.m_element)
        }
    }

    selectShape(selectedShape: ShapeView) {
        const shape = selectedShape.getModel()
        this.m_onFrameChangeUnsubscribe = shape.getOnFrameChanged().add(() => this.resizeSelector(shape))
        this.resizeSelector(shape)
        this.m_canvas.getDOMElement().appendChild(this.m_element)
        this.m_resizeHandler.handle(selectedShape)
    }

    private resizeSelector(shape: Shape) {
        this.m_element.style.left = shape.getLeft() + 'px'
        this.m_element.style.top = shape.getTop() + 'px'
        this.m_element.style.width = shape.getWidth() + 'px'
        this.m_element.style.height = shape.getHeight() + 'px'
    }
}

export {
    SelectionView
}