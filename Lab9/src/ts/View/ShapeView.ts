import { Shape } from "../Model/Shape";
import { ShapeController } from "../Controller/ShapeController";
import { DragAndDropHandler } from "./DragAndDropHandler";
import { ResizeHandler } from "./ResizeHandler";
import {ISignal, Signal} from "../Signal";

abstract class ShapeView
{
    private readonly m_model: Shape
    private readonly m_controller: ShapeController
    private readonly m_canvas: HTMLElement
    private m_dragAndDropHandler: DragAndDropHandler
    private m_resizeHandler: ResizeHandler
    private m_element: HTMLElement = document.createElement('div');
    private m_shapeSelected: ISignal<number> = new Signal()
    private m_isSelected: boolean = false

    protected constructor(model: Shape, canvas: HTMLElement) {
        this.m_model = model
        this.m_controller = new ShapeController(model, this)
        this.m_canvas = canvas
        this.m_dragAndDropHandler = new DragAndDropHandler(this.m_model, this.m_canvas, this.m_controller, this.m_element)
        this.m_resizeHandler = new ResizeHandler(this.m_model, this.m_canvas, this.m_controller, this.m_element)
        this.m_model.getOnFrameChanged().add(() => this.rerender())
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

    setIsSelected(isSelected: boolean) {
        this.m_isSelected = isSelected
        this.rerender()
    }

    rerender() {
        const left = this.m_model.getLeft()
        const top = this.m_model.getTop()
        const width = this.m_model.getWidth()
        const height = this.m_model.getHeight()

        this.m_element.style.left = `${left}px`
        this.m_element.style.top = `${top}px`
        this.m_element.style.width = `${width}px`
        this.m_element.style.height = `${height}px`
        this.m_element.style.position = 'absolute'
        this.m_element.style.boxShadow = this.m_isSelected ? '0 0 0 1px black' : ''
        const svg = this.m_element.getElementsByTagName('svg')[0]
        if (svg) {
            svg.outerHTML = this.getShapeHtmlImpl()
        } else {
            this.m_element.innerHTML = this.getShapeHtmlImpl()
        }
    }

    render() {
        this.m_element.innerHTML = ''
        this.m_element.remove()
        this.rerender()
        if (this.m_isSelected) {
            this.m_resizeHandler.handle()
        }
        this.m_element.onmousedown = e => this.m_dragAndDropHandler.handle(e)
        this.m_canvas.appendChild(this.m_element)
    }
}

export {
    ShapeView,
}