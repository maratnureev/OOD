import {SelectionController} from "../Controller/SelectionController";
import {ResizeHandler} from "./ResizeHandler";
import {Canvas} from "../Model/Canvas";
import {Shape} from "../Model/Shape";
import { Selection } from "../Model/Selection";

class SelectionView {
    private readonly m_element: HTMLElement
    private readonly m_controller: SelectionController
    private readonly m_selection: Selection
    private m_onFrameChangeUnsubscribe: (() => void)|null = null
    private m_resizeHandler: ResizeHandler
    private m_parentElement: HTMLElement

    constructor(parentElement: HTMLElement, canvasModel: Canvas, selectionModel: Selection) {
        this.m_element = document.createElement('div')
        this.m_element.style.boxShadow = '0 0 0 1px black'
        this.m_element.style.position = 'absolute'
        this.m_element.style.pointerEvents = 'none'
        this.m_parentElement = parentElement
        this.m_selection = selectionModel
        this.m_controller = new SelectionController(canvasModel, this.m_selection)
        this.m_resizeHandler = new ResizeHandler(parentElement, this.m_element, this.m_controller)
        this.m_selection.getOnSelectedShapeChanged().add(
            (shape) => {
                if (shape === null) {
                    this.removeSelection()
                } else {
                    this.selectShape(shape)
                }
            }
        )
    }

    removeSelection() {
        if (this.m_onFrameChangeUnsubscribe !== null) {
            this.m_onFrameChangeUnsubscribe()
            this.m_onFrameChangeUnsubscribe = null
            this.m_parentElement.removeChild(this.m_element)
        }
    }

    selectShape(selectedShape: Shape) {
        this.m_onFrameChangeUnsubscribe = selectedShape.getOnFrameChanged().add(() => this.resizeSelector(selectedShape))
        this.resizeSelector(selectedShape)
        this.m_parentElement.appendChild(this.m_element)
        this.m_resizeHandler.handle(selectedShape)
    }

    private resizeSelector(shape: Shape) {
        const shapeFrame = shape.getFrame()
        this.m_element.style.left = shapeFrame.left + 'px'
        this.m_element.style.top = shapeFrame.top + 'px'
        this.m_element.style.width = shapeFrame.width + 'px'
        this.m_element.style.height = shapeFrame.height + 'px'
    }
}

export {
    SelectionView
}