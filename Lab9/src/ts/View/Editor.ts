import {Shape} from "../Model/Shape";
import {ToolbarView} from "./ToolbarView";
import {ShapeType} from "../Model/ShapeType";
import {CanvasView} from "./CanvasView";
import {Canvas} from "../Model/Canvas";
import {ToolbarController} from "../Controller/ToolbarController";
import { Selection } from "../Model/Selection";
import { JsonSerializer, SerializedCanvas, Serializer } from "../Serializer";
import { JsonFileManager, FileManager } from "../Loader";

const DEFAULT_SHAPE_WIDTH = 100;
const DEFAULT_SHAPE_HEIGHT = 100;
const DEFAULT_CANVAS_WIDTH = 640;
const DEFAULT_CANVAS_HEIGHT = 480

class Editor {
    private readonly m_element: HTMLElement
    private readonly m_toolbarView: ToolbarView
    private m_canvasModel: Canvas
    private m_canvasView: CanvasView
    private m_controller: ToolbarController
    private m_selectionModel: Selection
    private m_fileManager: FileManager
    private m_serializer: Serializer

    constructor() {
        this.m_element = document.getElementById("editor") as HTMLElement
        this.m_toolbarView = new ToolbarView(
            () => this.createShape(ShapeType.Rectangle),
            () => this.createShape(ShapeType.Triangle),
            () => this.createShape(ShapeType.Ellipse),
            () => this.deleteShape(),
            () => this.saveDocument(),
            () => this.m_fileManager.uploadFile((canvas) => this.loadDocument(canvas)),
            this.m_element
        )
        const canvasContext = this.createCanvasContext(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT)
        this.m_serializer = new JsonSerializer
        this.m_fileManager = new JsonFileManager
        this.m_canvasModel = canvasContext.canvasModel
        this.m_selectionModel = canvasContext.selection
        this.m_controller = new ToolbarController(this.m_canvasModel)
        this.m_canvasView = canvasContext.canvasView
        const onDeleteButtonPressed = (e: KeyboardEvent) => {
            if (e.key === 'Delete') {
                this.deleteShape()
            }
        }
        window.addEventListener('keydown', onDeleteButtonPressed)
    }

    private createShape(type: ShapeType) {
        const frame = {
            left: (this.m_canvasModel.getWidth() - DEFAULT_SHAPE_WIDTH) / 2,
            top: (this.m_canvasModel.getHeight() - DEFAULT_SHAPE_HEIGHT) / 2,
            width: DEFAULT_SHAPE_WIDTH,
            height: DEFAULT_SHAPE_HEIGHT,
        }
        const id = window.btoa(new Date().getTime().toString())
        const shape: Shape = new Shape(
            id,
            frame,
            type,
            this.m_canvasModel
        )
        this.m_controller.addShape(shape)
    }

    private deleteShape() {
        const selectedShape = this.m_selectionModel.getSelectedShape()
        if (selectedShape !== null) {
            this.m_controller.removeShape(selectedShape.getId())
        }
    }

    private createCanvasContext(width: number, height: number) {
        const canvasModel = new Canvas(width, height)
        const selection = new Selection
        const canvasView = new CanvasView(canvasModel, selection, this.m_element)    
        return {
            canvasModel,
            selection,
            canvasView
        }
    }   

    private saveDocument() {
        this.m_fileManager.saveFile(this.m_serializer.serializeCanvas(this.m_canvasModel), 'canvas.json')
    }

    private loadDocument(canvas: SerializedCanvas) {
        this.m_canvasView.remove()
        const canvasContext = this.createCanvasContext(canvas.width, canvas.height)
        this.m_canvasModel = canvasContext.canvasModel
        this.m_selectionModel = canvasContext.selection
        this.m_canvasView = canvasContext.canvasView
        const shapes = canvas.shapes.map(shape => new Shape(shape.id, shape.frame, shape.type, this.m_canvasModel))
        shapes.forEach(shape => {
            this.m_canvasModel.addShape(shape)
        })
    }
}

export {
    Editor
}