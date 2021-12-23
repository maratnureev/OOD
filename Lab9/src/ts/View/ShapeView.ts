import { Shape } from "../Model/Shape";
import { ShapeController } from "../Controller/ShapeController";
import { DragAndDropHandler } from "./DragAndDropHandler";
import {IEvent, Event} from "../Event";
import {CanvasView} from "./CanvasView";

abstract class ShapeView
{
    private readonly m_shape: Shape
    private readonly m_controller: ShapeController
    private readonly parentElement: HTMLElement
    private m_dragAndDropHandler: DragAndDropHandler
    private m_element: HTMLElement = document.createElement('div');
    private m_shapeSelected: IEvent<string> = new Event()

    protected constructor(shape: Shape, parentElement: HTMLElement) {
        this.m_shape = shape
        this.m_controller = new ShapeController(shape)
        this.parentElement = parentElement
        this.m_dragAndDropHandler = new DragAndDropHandler(this.m_shape, this.parentElement, this.m_controller, this.m_element)
        // При undo/redo отписываться от события
        this.m_shape.getOnFrameChanged().add(() => this.resize())
        this.m_dragAndDropHandler.getShapeSelected().add(() => {
            this.m_shapeSelected.dispatch(this.m_shape.getId())
        })
    }

    protected abstract getShapeSVG(): string

    getModel() {
        return this.m_shape
    }

    getShapeSelected() {
        return this.m_shapeSelected
    }

    remove() {
        this.m_element.remove()
    }

    resize() {
        const frame = this.m_shape.getFrame()

        this.m_element.style.left = `${frame.left}px`
        this.m_element.style.top = `${frame.top}px`
        this.m_element.style.width = `${frame.width}px`
        this.m_element.style.height = `${frame.height}px`
        this.m_element.style.position = 'absolute'
        this.m_element.innerHTML = this.getShapeSVG()
    }

    render(parentElement: HTMLElement) {
        this.m_element.remove()
        this.resize()
        this.m_element.onmousedown = e => this.m_dragAndDropHandler.handle(e)
        parentElement.appendChild(this.m_element)
    }
}

export {
    ShapeView
}