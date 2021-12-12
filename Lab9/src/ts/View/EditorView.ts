import {ShapeView} from "./ShapeView";
import {Editor} from "../Model/Editor";
import {EditorController} from "../Controller/EditorController";
import {Shape} from "../Model/Shape";
import {RectangleView} from "./RectangleView";
import {ToolbarView} from "./ToolbarView";
import {TriangleView} from "./TriangleView";
import {EllipseView} from "./EllipseView";
import {ShapeType} from "../Model/ShapeType";

const DEFAULT_SHAPE_WIDTH = 100;
const DEFAULT_SHAPE_HEIGHT = 100;

class EditorView {

    private readonly m_model: Editor
    private readonly m_controller: EditorController
    private readonly m_canvas: HTMLElement
    private readonly m_editor: HTMLElement
    private m_toolbarView: ToolbarView
    private m_shapeViews: Map<number, ShapeView> = new Map()
    private m_shapeIdCounter: number = 0
    private m_selectedShapeId: number | null = null

    constructor(model: Editor, editor: HTMLElement) {
        this.m_model = model
        this.m_controller = new EditorController(model, this)
        this.m_editor = editor
        this.m_canvas = document.createElement('div')
        this.m_canvas.classList.add('canvas')
        this.m_canvas.style.width = `${this.m_model.getWidth()}px`
        this.m_canvas.style.height = `${this.m_model.getHeight()}px`
        this.m_model.getOnShapesChanged().add(
            (shapeId) => this.onShapeChanged(shapeId)
        )
        this.m_toolbarView = new ToolbarView(
            () => this.createRectangle(),
            () => this.createTriangle(),
            () => this.createEllipse(),
            () => this.deleteShape()
        )
        window.onkeydown = e => {
            if (e.key === 'Delete') {
                this.deleteShape()
            }
        }
    }

    render() {
        this.m_canvas.innerHTML = ''
        this.m_canvas.onmousedown = e => {
            if (!e.defaultPrevented) {
                if (this.m_selectedShapeId !== null) {
                    const selectedShape = this.m_shapeViews.get(this.m_selectedShapeId)
                    if (selectedShape) {
                        selectedShape.setIsSelected(false)
                    }
                }
                this.m_selectedShapeId = null
                this.render()
            }
        }
        this.m_toolbarView.render(this.m_editor)
        this.m_editor.appendChild(this.m_canvas)
        this.m_shapeViews.forEach(
            (shapeView: ShapeView) => {
                shapeView.render()
            }
        )
    }

    private onShapeChanged(shapeId: number) {
        const shape = this.m_model.getShapeById(shapeId)
        if (!shape) {
            this.m_shapeViews.delete(shapeId)
        } else {
            let view: ShapeView
            switch (shape.getType()) {
                case ShapeType.Ellipse:
                    view = new EllipseView(shape, this.m_canvas)
                    break
                case ShapeType.Rectangle:
                    view = new RectangleView(shape, this.m_canvas)
                    break
                case ShapeType.Triangle:
                    view = new TriangleView(shape, this.m_canvas)
                    break
            }
            this.m_shapeViews.set(shapeId, view)
            view.getShapeSelected().add((shapeId) => {
                if (this.m_selectedShapeId !== null) {
                    const selectedShape = this.m_shapeViews.get(this.m_selectedShapeId)
                    if (selectedShape) {
                        selectedShape.setIsSelected(false)
                    }
                }
                this.m_selectedShapeId = shapeId
                view.setIsSelected(true)
                this.render()
            })
        }
        this.render()
    }

    private createRectangle() {
        const shape: Shape = new Shape(
            this.m_shapeIdCounter++,
            ShapeType.Rectangle,
            (this.m_model.getWidth() - DEFAULT_SHAPE_WIDTH) / 2,
            (this.m_model.getHeight() - DEFAULT_SHAPE_HEIGHT) / 2,
            DEFAULT_SHAPE_WIDTH,
            DEFAULT_SHAPE_HEIGHT
        )
        this.m_controller.addShape(shape)
        this.render()
    }

    private createEllipse() {
        const shape: Shape = new Shape(
            this.m_shapeIdCounter++,
            ShapeType.Ellipse,
            (this.m_model.getWidth() - DEFAULT_SHAPE_WIDTH) / 2,
            (this.m_model.getHeight() - DEFAULT_SHAPE_HEIGHT) / 2,
            DEFAULT_SHAPE_WIDTH,
            DEFAULT_SHAPE_HEIGHT
        )
        this.m_controller.addShape(shape)
        this.render()
    }

    private createTriangle() {
        const shape: Shape = new Shape(
            this.m_shapeIdCounter++,
            ShapeType.Triangle,
            (this.m_model.getWidth() - DEFAULT_SHAPE_WIDTH) / 2,
            (this.m_model.getHeight() - DEFAULT_SHAPE_HEIGHT) / 2,
            DEFAULT_SHAPE_WIDTH,
            DEFAULT_SHAPE_HEIGHT
        )
        this.m_controller.addShape(shape)
        this.render()
    }

    private deleteShape() {
        if (this.m_selectedShapeId !== null) {
            this.m_controller.removeShape(this.m_selectedShapeId)
        }
    }
}

export {
    EditorView
}