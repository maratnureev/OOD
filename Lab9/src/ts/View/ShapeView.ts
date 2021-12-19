import { Shape } from "../Model/Shape";
import { ShapeController } from "../Controller/ShapeController";
import { DragAndDropHandler } from "./DragAndDropHandler";
import { ResizeHandler } from "./ResizeHandler";
import {ISignal, Signal} from "../Signal";
import {CanvasView} from "./CanvasView";

abstract class ShapeView
{
    private readonly m_model: Shape
    private readonly m_controller: ShapeController
    private readonly m_canvas: CanvasView
    private m_dragAndDropHandler: DragAndDropHandler
    private m_element: HTMLElement = document.createElement('div');
    private m_shapeSelected: ISignal<number> = new Signal()

    protected constructor(model: Shape, canvas: CanvasView) {
        this.m_model = model
        this.m_controller = new ShapeController(model, this)
        this.m_canvas = canvas
        this.m_dragAndDropHandler = new DragAndDropHandler(this.m_model, this.m_canvas, this.m_controller, this.m_element)
        this.m_model.getOnFrameChanged().add(() => this.resize())
        this.m_dragAndDropHandler.getShapeSelected().add(() => {
            this.m_shapeSelected.dispatch(this.m_model.getId())
        })
    }

    abstract getShapeHtmlImpl(): string

    getModel() {
        return this.m_model
    }

    getShapeSelected() {
        return this.m_shapeSelected
    }

    getDOMElement() {
        return this.m_element
    }

    remove() {
        this.m_element.remove()
    }

    resize() {
        const left = this.m_model.getLeft()
        const top = this.m_model.getTop()
        const width = this.m_model.getWidth()
        const height = this.m_model.getHeight()

        this.m_element.style.left = `${left}px`
        this.m_element.style.top = `${top}px`
        this.m_element.style.width = `${width}px`
        this.m_element.style.height = `${height}px`
        this.m_element.style.position = 'absolute'
        const svg = this.m_element.getElementsByTagName('svg')[0]
        if (svg) {
            svg.outerHTML = this.getShapeHtmlImpl()
        } else {
            this.m_element.innerHTML = this.getShapeHtmlImpl()
        }
    }

    render(parentElement: HTMLElement) {
        this.m_element.innerHTML = ''
        this.m_element.remove()
        this.resize()
        this.m_element.onmousedown = e => this.m_dragAndDropHandler.handle(e)
        parentElement.appendChild(this.m_element)
    }

    setFrame(left: number, top: number, width: number, height: number) {
        this.m_controller.setFrame(left, top, width, height)
    }
}

export {
    ShapeView,
}