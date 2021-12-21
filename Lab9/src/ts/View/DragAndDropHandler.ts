import {ShapeController} from "../Controller/ShapeController";
import {Shape} from "../Model/Shape";
import {IEvent, Event} from "../Event";
import {CanvasView} from "./CanvasView";


// Передавать HTMLelement вместо канваса
class DragAndDropHandler {
    private readonly m_controller: ShapeController
    private readonly m_model: Shape
    private m_canvas: CanvasView
    private m_element: HTMLElement
    private m_shapeSelected: IEvent<void> = new Event()
    private m_mouseMovedCallback: (e:MouseEvent) => void = () => {}
    private m_mouseUpCallback: () => void = () => {}

    constructor(model: Shape, canvas: CanvasView, controller: ShapeController, element: HTMLElement) {
        this.m_model = model
        this.m_controller = controller
        this.m_canvas = canvas
        this.m_element = element;
    }

    public handle(e: MouseEvent) {
        this.onShapeMouseDown(e)
    }

    public getShapeSelected() {
        return this.m_shapeSelected
    }

    private onShapeMouseUp() {
        window.removeEventListener('mousemove', this.m_mouseMovedCallback)
        window.removeEventListener('mouseup', this.m_mouseUpCallback)
    }

    private onShapeMove(e: MouseEvent, leftOffset: number, topOffset: number) {
        this.m_controller.setFrame(
            e.x - leftOffset,
            e.y - topOffset,
            this.m_model.getWidth(),
            this.m_model.getHeight(),
        )
    }

    private onShapeMouseDown(e: MouseEvent) {
        if (!e.defaultPrevented) {
            e.preventDefault()
            const canvasBounders = this.m_canvas.getCanvasBounders()
            const elementBounds = this.m_element.getBoundingClientRect()
            const resultLeftOffset = canvasBounders.left + (e.x - elementBounds.left)
            const resultTopOffset = canvasBounders.top + (e.y - elementBounds.top)
            this.m_shapeSelected.dispatch()
            this.m_mouseMovedCallback = (e: MouseEvent) => this.onShapeMove(e, resultLeftOffset, resultTopOffset)
            this.m_mouseUpCallback = () => this.onShapeMouseUp()
            window.addEventListener('mousemove', this.m_mouseMovedCallback)
            window.addEventListener('mouseup', this.m_mouseUpCallback)
        }
    }
}

export {
    DragAndDropHandler,
}