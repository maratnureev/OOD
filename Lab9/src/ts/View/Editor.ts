import {Shape} from "../Model/Shape";
import {ToolbarView} from "./ToolbarView";
import {ShapeType} from "../Model/ShapeType";
import {CanvasView} from "./CanvasView";
import {Canvas, SerializedCanvas} from "../Model/Canvas";
import {ToolbarController} from "../Controller/ToolbarController";

const DEFAULT_SHAPE_WIDTH = 100;
const DEFAULT_SHAPE_HEIGHT = 100;
const DEFAULT_CANVAS_WIDTH = 640;
const DEFAULT_CANVAS_HEIGHT = 480

class Editor {
    private readonly m_element: HTMLElement
    private m_canvasModel: Canvas
    private m_canvasView: CanvasView
    private m_controller: ToolbarController
    private m_toolbarView: ToolbarView

    constructor() {
        this.m_element = document.getElementById("editor") as HTMLElement
        this.m_canvasModel = new Canvas(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT)
        this.m_canvasView = new CanvasView(this.m_canvasModel)
        this.m_controller = new ToolbarController(this.m_canvasModel)
        this.m_toolbarView = new ToolbarView(
            () => this.createShape(ShapeType.Rectangle),
            () => this.createShape(ShapeType.Triangle),
            () => this.createShape(ShapeType.Ellipse),
            () => this.deleteShape(),
            () => this.saveDocument(),
            () => this.uploadFile((object) => this.uploadDocument(object))
        )
        const onDeleteButtonPressed = (e: KeyboardEvent) => {
            if (e.key === 'Delete') {
                this.deleteShape()
            }
        }
        window.addEventListener('keydown', onDeleteButtonPressed)
        this.render()
    }

    private render() {
        this.m_toolbarView.render(this.m_element)
        this.m_canvasView.render(this.m_element)
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
        this.render()
    }

    private deleteShape() {
        const selectedShapeId = this.m_canvasModel.getSelectedShapeId()
        if (selectedShapeId !== null) {
            this.m_controller.selectShape(null)
            this.m_controller.removeShape(selectedShapeId)
        }
    }

    private saveDocument() {
        Editor.saveFile(JSON.stringify(this.m_canvasModel.serialize()), 'canvas.json')
    }

    private uploadDocument(document: Object) {
        let canvas = document as SerializedCanvas
        this.m_canvasView.remove()
        this.m_canvasModel = new Canvas(canvas.width, canvas.height)
        this.m_canvasView = new CanvasView(this.m_canvasModel)
        const shapes = canvas.shapes.map(shape => new Shape(shape.id, shape.frame, shape.type, this.m_canvasModel))
        shapes.forEach(shape => {
            this.m_canvasModel.addShape(shape)
        })
        this.m_canvasView.render(this.m_element)
    }

    private static saveFile(content: string, fileName: string) {
        const a = document.createElement('a')
        const file = new Blob([content], {type: 'text/plain'})
        a.href = URL.createObjectURL(file)
        a.download = fileName
        a.click()
    }

    private uploadFile(onUploadCallback: (result: Object) => void) {
        const input = document.createElement('input')
        input.setAttribute('type', 'file')
        input.click()
        input.addEventListener("change", () => {
            const reader = new FileReader()
            const selectedFile =  input.files && input.files[0]
            if (selectedFile) {
                reader.onload = () => {
                    if (typeof reader.result === 'string') {
                        try {
                            onUploadCallback(JSON.parse(reader.result))
                        } catch (e) {
                            alert('Invalid json file')
                        }
                    }
                }
                reader.readAsText(selectedFile)
            }
        })
    }
}

export {
    Editor
}