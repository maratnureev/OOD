import {ShapeController} from "../Controller/ShapeController";
import {Shape} from "../Model/Shape";
import {ISignal, Signal} from "../Signal";

class DragAndDropHandler {
    private readonly m_controller: ShapeController
    private readonly m_model: Shape
    private m_canvas: HTMLElement
    private m_element: HTMLElement
    private m_shapeSelected: ISignal<void> = new Signal()

    constructor(model: Shape, canvas: HTMLElement, controller: ShapeController, element: HTMLElement) {
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

    private static onShapeMouseUp() {
        window.onmousemove = null
        window.onmouseup = null
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
            const canvasBounders = this.m_canvas.getBoundingClientRect()
            const elementBounds = this.m_element.getBoundingClientRect()
            const resultLeftOffset = canvasBounders.left + (e.x - elementBounds.left)
            const resultTopOffset = canvasBounders.top + (e.y - elementBounds.top)
            this.m_shapeSelected.dispatch()
            window.onmousemove = e => this.onShapeMove(e, resultLeftOffset, resultTopOffset)
            window.onmouseup = () => DragAndDropHandler.onShapeMouseUp()
        }
    }
}

export {
    DragAndDropHandler,
}