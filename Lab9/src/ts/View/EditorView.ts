import {Shape} from "../Model/Shape";
import {ToolbarView} from "./ToolbarView";
import {ShapeType} from "../Model/ShapeType";
import {CanvasView} from "./CanvasView";
import {Canvas} from "../Model/Canvas";

const DEFAULT_SHAPE_WIDTH = 100;
const DEFAULT_SHAPE_HEIGHT = 100;
const DEFAULT_CANVAS_WIDTH = 640;
const DEFAULT_CANVAS_HEIGHT = 480

class EditorView {
    private readonly m_editor: HTMLElement
    private readonly m_canvasModel: Canvas
    private m_canvasView: CanvasView
    private m_toolbarView: ToolbarView
    private m_shapeIdCounter: number = 0

    constructor() {
        this.m_editor = document.getElementById("editor") as HTMLElement
        const editorBounders = this.m_editor.getBoundingClientRect()
        const left = editorBounders.width / 2
        const top = editorBounders.height / 2
        this.m_canvasModel = new Canvas(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT, left, top)
        this.m_canvasView = new CanvasView(this.m_canvasModel)
        this.m_toolbarView = new ToolbarView(
            () => this.createShape(ShapeType.Rectangle),
            () => this.createShape(ShapeType.Triangle),
            () => this.createShape(ShapeType.Ellipse),
            () => this.deleteShape()
        )
    }

    render() {
        this.m_toolbarView.render(this.m_editor)
        this.m_canvasView.render(this.m_editor)
    }

    private createShape(type: ShapeType) {
        const shape: Shape = new Shape(
            this.m_shapeIdCounter++,
            type,
            (this.m_canvasModel.getWidth() - DEFAULT_SHAPE_WIDTH) / 2,
            (this.m_canvasModel.getHeight() - DEFAULT_SHAPE_HEIGHT) / 2,
            DEFAULT_SHAPE_WIDTH,
            DEFAULT_SHAPE_HEIGHT,
            this.m_canvasModel
        )
        this.m_canvasView.addShape(shape)
        this.render()
    }

    private deleteShape() {
        this.m_canvasView.deleteShape()
    }
}

export {
    EditorView
}