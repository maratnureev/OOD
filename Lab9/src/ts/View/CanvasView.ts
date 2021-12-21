import {CanvasController} from "../Controller/CanvasController";
import {Canvas} from "../Model/Canvas";
import {ShapeView} from "./ShapeView";
import {ShapeType} from "../Model/ShapeType";
import {EllipseView} from "./EllipseView";
import {RectangleView} from "./RectangleView";
import {TriangleView} from "./TriangleView";
import {Shape} from "../Model/Shape";
import {SelectionView} from "./SelectionView";

class CanvasView {
    private readonly m_canvas: HTMLElement
    private m_controller: CanvasController
    private m_model: Canvas
    private m_shapeViews: Map<number, ShapeView> = new Map()
    private m_selectionView: SelectionView


    // Синхронизировать модель со view
    constructor(model: Canvas) {
        this.m_model = model
        this.m_controller = new CanvasController(model, this)
        this.m_selectionView = new SelectionView(this)
        this.m_canvas = document.createElement('div')
        this.m_canvas.classList.add('canvas')
        this.m_canvas.style.width = `${this.m_model.getWidth()}px`
        this.m_canvas.style.height = `${this.m_model.getHeight()}px`
        this.m_canvas.style.left = `${this.m_model.getLeft()}px` //Убрать координаты left, top в модели 
        this.m_canvas.style.top = `${this.m_model.getTop()}px`
        this.m_model.getOnShapesChanged().add(
            (shapeId) => this.onShapeChanged(shapeId)
        )
        this.m_model.getOnSelectedShapeChanged().add(
            (shapeId) => this.selectShape(shapeId)
        )
        const onDeleteButtonPressed = (e: KeyboardEvent) => {
            if (e.key === 'Delete') {
                this.deleteShape()
            }
        }
        this.m_canvas.addEventListener('keydown', onDeleteButtonPressed) // Подписываться на событие не для окна
    }


    //render можно вызвать несколько раз
    render(parentElement: HTMLElement) {
        const onShapeSelectedCallback = (e: MouseEvent) => {
            if (!e.defaultPrevented) {
                this.m_controller.selectShape(null)
            }
        }
        this.m_canvas.addEventListener('mousedown', onShapeSelectedCallback)
        parentElement.appendChild(this.m_canvas)
        this.m_shapeViews.forEach(
            (shapeView: ShapeView) => {
                shapeView.render(this.m_canvas)
            }
        )
    }

    // Сделать контроллер для меню
    addShape(shape: Shape) {
        this.m_controller.addShape(shape)
    }

    // Сделать контроллер для меню
    deleteShape() {
        const selectedShapeId = this.m_model.getSelectedShapeId()
        if (selectedShapeId !== null) {
            this.selectShape(null)
            this.m_controller.removeShape(selectedShapeId)
        }
    }

    getCanvasBounders() {
        return this.m_canvas.getBoundingClientRect()
    }

    getDOMElement() {
        return this.m_canvas
    }

    private selectShape(shapeId: number|null) {
        if (shapeId === null) {
            this.m_selectionView.removeSelection()
            return
        }
        const selectedShape = this.m_shapeViews.get(shapeId)
        if (selectedShape) {
            this.m_selectionView.selectShape(selectedShape)
        }
    }


    //Выделить в 2 события
    private onShapeChanged(shapeId: number) {
        const shape = this.m_model.getShapeById(shapeId)
        const shapeView = this.m_shapeViews.get(shapeId)
        if (!shape) {
            if (shapeView) {
                shapeView.remove()
            }
            this.m_shapeViews.delete(shapeId)
        } else {
            let view: ShapeView
            switch (shape.getType()) {
                case ShapeType.Ellipse:
                    view = new EllipseView(shape, this)
                    break
                case ShapeType.Rectangle:
                    view = new RectangleView(shape, this)
                    break
                case ShapeType.Triangle:
                    view = new TriangleView(shape, this)
                    break
            }
            this.m_shapeViews.set(shapeId, view)
            view.getShapeSelected().add((shapeId) => {
                this.m_controller.selectShape(shapeId)
            })
        }
    }
}

export {
    CanvasView
}