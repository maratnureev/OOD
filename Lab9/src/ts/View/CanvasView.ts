import {CanvasController} from "../Controller/CanvasController";
import {Canvas} from "../Model/Canvas";
import {ShapeView} from "./ShapeView";
import {ShapeType} from "../Model/ShapeType";
import {EllipseView} from "./EllipseView";
import {RectangleView} from "./RectangleView";
import {TriangleView} from "./TriangleView";
import {SelectionView} from "./SelectionView";
import { Selection } from "../Model/Selection";

class CanvasView {
    private readonly m_element: HTMLElement
    private readonly m_canvasModel: Canvas
    private readonly m_selectionModel: Selection
    private readonly m_selectionView: SelectionView
    private m_controller: CanvasController
    private m_shapeViews: Map<string, ShapeView> = new Map()

    constructor(canvas: Canvas, selection: Selection, parentElement: HTMLElement) {
        this.m_canvasModel = canvas
        this.m_selectionModel = selection
        this.m_controller = new CanvasController(selection)
        this.m_element = document.createElement('div')
        this.m_element.classList.add('canvas')
        this.m_element.style.width = `${this.m_canvasModel.getWidth()}px`
        this.m_element.style.height = `${this.m_canvasModel.getHeight()}px`
        this.m_element.style.boxShadow = '0 0 0 2px black'
        this.m_selectionView = new SelectionView(this.m_element, this.m_canvasModel, this.m_selectionModel)
        this.m_canvasModel.getShapeIds().forEach(
            (shapeId ) => this.createShapeView(shapeId)
        )
        this.m_canvasModel.getOnShapeAdded().add(
            (shapeId) => this.createShapeView(shapeId)
        )
        this.m_canvasModel.getOnShapeRemoved().add(
            (shapeId) => {
                this.removeShapeView(shapeId)
                this.m_controller.selectShape(null)
            }
        )
        
        this.render(parentElement)
    }

    remove() {
        this.m_element.remove()
    }

    private render(parentElement: HTMLElement) {
        const onShapeSelectedCallback = (e: MouseEvent) => {
            if (!e.defaultPrevented) {
                this.m_controller.selectShape(null)
            }
        }
        this.m_element.addEventListener('mousedown', onShapeSelectedCallback)
        parentElement.appendChild(this.m_element)
    }
    
    private removeShapeView(shapeId: string) {
        const shapeView = this.m_shapeViews.get(shapeId)
        if (shapeView) {
            shapeView.remove()
        }
        this.m_shapeViews.delete(shapeId)
    }

    private createShapeView(shapeId: string) {
        const shape = this.m_canvasModel.getShapeById(shapeId)
        if (!shape) {
            return
        }
        let view: ShapeView
        switch (shape.getType()) {
            case ShapeType.Ellipse:
                view = new EllipseView(shape, this.m_element)
                break
            case ShapeType.Rectangle:
                view = new RectangleView(shape, this.m_element)
                break
            case ShapeType.Triangle:
                view = new TriangleView(shape, this.m_element)
                break
        }
        this.m_shapeViews.set(shapeId, view)
        view.getShapeSelected().add((shapeId) => {
            const shape = this.m_canvasModel.getShapeById(shapeId)
            if (shape) {
                this.m_controller.selectShape(shape)
            }
        })
    }
}

export {
    CanvasView
}