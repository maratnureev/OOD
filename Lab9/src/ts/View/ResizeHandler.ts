import {CanvasView} from "./CanvasView";
import {ShapeView} from "./ShapeView";

type HandlerType = 'leftTop' | 'rightTop' | 'leftBottom' | 'rightBottom'

class ResizeHandler {
    private readonly m_element: HTMLElement
    private m_canvas: CanvasView
    private m_onMouseMoveCallback: (e: MouseEvent) => void = () => {}
    private m_onMouseUpCallback: () => void = () => {}

    constructor(canvas: CanvasView, element: HTMLElement) {
        this.m_canvas = canvas
        this.m_element = element;
    }

    public handle(shapeView: ShapeView) {
        this.addResizeHandlers(this.m_element, shapeView)
    }

    private static createResizeController(handler: HTMLElement, handlerType: HandlerType) {
        handler.style.width = '7px'
        handler.style.height = '7px'
        handler.style.position = 'absolute'
        handler.style.background = 'blue'
        handler.style.pointerEvents = 'all'

        switch (handlerType) {
            case "leftBottom":
                handler.style.bottom = '-5px'
                handler.style.left = '-5px'
                break
            case "leftTop":
                handler.style.top = '-5px'
                handler.style.left = '-5px'
                break
            case "rightBottom":
                handler.style.bottom = '-5px'
                handler.style.right = '-5px'
                break
            case "rightTop":
                handler.style.top = '-5px'
                handler.style.right = '-5px'
                break
        }
    }

    private addResizeHandlers(element: HTMLElement, shapeView: ShapeView) {
        const leftTopResizeController = document.createElement('div')
        const leftBottomResizeController = document.createElement('div')
        const rightTopResizeController = document.createElement('div')
        const rightBottomResizeController = document.createElement('div')

        ResizeHandler.createResizeController(leftTopResizeController, 'leftTop')
        ResizeHandler.createResizeController(leftBottomResizeController, 'leftBottom')
        ResizeHandler.createResizeController(rightTopResizeController, 'rightTop')
        ResizeHandler.createResizeController(rightBottomResizeController, 'rightBottom')

        leftTopResizeController.addEventListener('mousedown', this.buildOnMouseDownCallback("leftTop", shapeView))
        leftBottomResizeController.addEventListener('mousedown',  this.buildOnMouseDownCallback("leftBottom", shapeView))
        rightTopResizeController.addEventListener('mousedown', this.buildOnMouseDownCallback("rightTop", shapeView))
        rightBottomResizeController.addEventListener('mousedown',  this.buildOnMouseDownCallback("rightBottom", shapeView))

        element.appendChild(leftTopResizeController)
        element.appendChild(leftBottomResizeController)
        element.appendChild(rightTopResizeController)
        element.appendChild(rightBottomResizeController)
    }

    private onMouseUp() {
        window.removeEventListener('mousemove', this.m_onMouseMoveCallback)
        window.removeEventListener('mouseup', this.m_onMouseUpCallback)
    }

    private onMouseMove(e: MouseEvent, type: HandlerType, shapeView: ShapeView) {
        const canvasBounds = this.m_canvas.getCanvasBounders()
        const shape = shapeView.getModel()
        const mouseLeft = e.x - canvasBounds.left
        const mouseTop = e.y - canvasBounds.top
        switch (type) {
            case "leftTop":
                shapeView.setFrame(
                    mouseLeft,
                    mouseTop,
                    (shape.getLeft() - mouseLeft) + shape.getWidth(),
                    (shape.getTop() - mouseTop) + shape.getHeight(),
                )
                break
            case "rightTop":
                shapeView.setFrame(
                    shape.getLeft(),
                    mouseTop,
                    mouseLeft - shape.getLeft(),
                    (shape.getTop() - mouseTop) + shape.getHeight(),
                )
                break
            case "leftBottom":
                shapeView.setFrame(
                    mouseLeft,
                    shape.getTop(),
                    (shape.getLeft() - mouseLeft) + shape.getWidth(),
                    mouseTop - shape.getTop(),
                )
                break
            case "rightBottom":
                shapeView.setFrame(
                    shape.getLeft(),
                    shape.getTop(),
                    mouseLeft - shape.getLeft(),
                    mouseTop - shape.getTop(),
                )
                break
        }
    }

    private buildOnMouseDownCallback(type: HandlerType, shapeView: ShapeView) {
        return (e: MouseEvent) => {
            e.preventDefault()
            this.m_onMouseMoveCallback = (e) => {this.onMouseMove(e, type, shapeView)}
            this.m_onMouseUpCallback = () => {this.onMouseUp()}
            window.addEventListener('mousemove', this.m_onMouseMoveCallback)
            window.addEventListener('mouseup', this.m_onMouseUpCallback)
        }
    }
}

export {
    ResizeHandler
}