import {ShapeController} from "../Controller/ShapeController";
import {Shape} from "../Model/Shape";

type HandlerType = 'leftTop' | 'rightTop' | 'leftBottom' | 'rightBottom'

class ResizeHandler {
    private readonly m_controller: ShapeController
    private readonly m_model: Shape
    private readonly m_element: HTMLElement
    private m_canvas: HTMLElement

    public handle() {
        this.addResizeHandlers(this.m_element)
    }

    constructor(model: Shape, canvas: HTMLElement, controller: ShapeController, element: HTMLElement) {
        this.m_model = model
        this.m_controller = controller
        this.m_canvas = canvas
        this.m_element = element;
    }

    private static createResizeController(handler: HTMLElement, handlerType: HandlerType) {
        handler.style.width = '5px'
        handler.style.height = '5px'
        handler.style.position = 'absolute'
        handler.style.background = 'blue'

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

    private addResizeHandlers(element: HTMLElement) {
        const leftTopResizeController = document.createElement('div')
        const rightTopResizeController = document.createElement('div')
        const leftBottomResizeController = document.createElement('div')
        const rightBottomResizeController = document.createElement('div')

        ResizeHandler.createResizeController(leftTopResizeController, 'leftTop')
        ResizeHandler.createResizeController(rightTopResizeController, 'rightTop')
        ResizeHandler.createResizeController(leftBottomResizeController, 'leftBottom')
        ResizeHandler.createResizeController(rightBottomResizeController, 'rightBottom')

        rightTopResizeController.onmousedown = (e) => {
            e.preventDefault()
            window.onmousemove = (e) => {this.onMouseMove(e, 'rightTop')}
            window.onmouseup = () => {ResizeHandler.onMouseUp()}
        }
        leftTopResizeController.onmousedown = (e) => {
            e.preventDefault()
            window.onmousemove = (e) => {this.onMouseMove(e, 'leftTop')}
            window.onmouseup = () => {ResizeHandler.onMouseUp()}
        }
        rightBottomResizeController.onmousedown = (e) => {
            e.preventDefault()
            window.onmousemove = (e) => {this.onMouseMove(e, 'rightBottom')}
            window.onmouseup = () => {ResizeHandler.onMouseUp()}
        }
        leftBottomResizeController.onmousedown = (e) => {
            e.preventDefault()
            window.onmousemove = (e) => {this.onMouseMove(e, 'leftBottom')}
            window.onmouseup = () => {ResizeHandler.onMouseUp()}
        }
        element.appendChild(leftTopResizeController)
        element.appendChild(rightTopResizeController)
        element.appendChild(leftBottomResizeController)
        element.appendChild(rightBottomResizeController)
    }

    private static onMouseUp() {
        window.onmousemove = null
        window.onmouseup = null
    }

    private onMouseMove(e: MouseEvent, type: HandlerType) {
        const canvasBounds = this.m_canvas.getBoundingClientRect()
        const mouseLeft = e.x - canvasBounds.left
        const mouseTop = e.y - canvasBounds.top
        switch (type) {
            case "leftTop":
                this.m_controller.setFrame(
                    mouseLeft,
                    mouseTop,
                    Math.max((this.m_model.getLeft() - mouseLeft) + this.m_model.getWidth(), 0),
                    Math.max((this.m_model.getTop() - mouseTop) + this.m_model.getHeight(), 0)
                )
                break
            case "rightTop":
                this.m_controller.setFrame(
                    this.m_model.getLeft(),
                    mouseTop,
                    Math.max(mouseLeft - this.m_model.getLeft(), 0),
                    Math.max((this.m_model.getTop() - mouseTop) + this.m_model.getHeight(), 0)
                )
                break
            case "leftBottom":
                this.m_controller.setFrame(
                    mouseLeft,
                    this.m_model.getTop(),
                    Math.max((this.m_model.getLeft() - mouseLeft) + this.m_model.getWidth(), 0),
                    Math.max(mouseTop - this.m_model.getTop(), 0),
                )
                break
            case "rightBottom":
                this.m_controller.setFrame(
                    this.m_model.getLeft(),
                    this.m_model.getTop(),
                    Math.max(mouseLeft - this.m_model.getLeft(), 0),
                    Math.max(mouseTop - this.m_model.getTop(), 0),
                )
                break
        }
    }
}

export {
    ResizeHandler
}