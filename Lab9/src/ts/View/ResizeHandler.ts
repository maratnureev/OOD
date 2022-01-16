import {Shape} from "../Model/Shape";
import {SelectionController} from "../Controller/SelectionController";

const LEFT_TOP_HANDLER_TYPE = 'leftTop'
const LEFT_BOTTOM_HANDLER_TYPE = 'leftBottom'
const RIGHT_TOP_HANDLER_TYPE = 'rightTop'
const RIGHT_BOTTOM_HANDLER_TYPE = 'rightBottom'

class ResizeHandler {
    private readonly m_element: HTMLElement
    private m_parentElement: HTMLElement
    private m_controller: SelectionController
    private m_onMouseMoveCallback: (e: MouseEvent) => void = () => {}
    private m_onMouseUpCallback: () => void = () => {}

    constructor(parentElement: HTMLElement, element: HTMLElement, controller: SelectionController) {
        this.m_parentElement = parentElement
        this.m_element = element
        this.m_controller = controller
    }

    public handle(shape: Shape) {
        this.addResizeHandlers(this.m_element, shape)
    }

    private static createResizeController(handler: HTMLElement, handlerType: string) {
        handler.style.width = '7px'
        handler.style.height = '7px'
        handler.style.position = 'absolute'
        handler.style.background = 'blue'
        handler.style.pointerEvents = 'all'

        switch (handlerType) {
            case LEFT_BOTTOM_HANDLER_TYPE:
                handler.style.bottom = '-5px'
                handler.style.left = '-5px'
                break
            case LEFT_TOP_HANDLER_TYPE:
                handler.style.top = '-5px'
                handler.style.left = '-5px'
                break
            case RIGHT_TOP_HANDLER_TYPE:
                handler.style.top = '-5px'
                handler.style.right = '-5px'
                break
            case RIGHT_BOTTOM_HANDLER_TYPE:
                handler.style.bottom = '-5px'
                handler.style.right = '-5px'
                break
        }
    }

    private addResizeHandlers(element: HTMLElement, shape: Shape) {
        const leftTopResizeController = document.createElement('div')
        const leftBottomResizeController = document.createElement('div')
        const rightTopResizeController = document.createElement('div')
        const rightBottomResizeController = document.createElement('div')

        ResizeHandler.createResizeController(leftTopResizeController, LEFT_TOP_HANDLER_TYPE)
        ResizeHandler.createResizeController(leftBottomResizeController, LEFT_BOTTOM_HANDLER_TYPE)
        ResizeHandler.createResizeController(rightTopResizeController, RIGHT_TOP_HANDLER_TYPE)
        ResizeHandler.createResizeController(rightBottomResizeController, RIGHT_BOTTOM_HANDLER_TYPE)

        leftTopResizeController.addEventListener('mousedown', this.buildOnMouseDownCallback(LEFT_TOP_HANDLER_TYPE))
        leftBottomResizeController.addEventListener('mousedown',  this.buildOnMouseDownCallback(LEFT_BOTTOM_HANDLER_TYPE))
        rightTopResizeController.addEventListener('mousedown', this.buildOnMouseDownCallback(RIGHT_TOP_HANDLER_TYPE))
        rightBottomResizeController.addEventListener('mousedown',  this.buildOnMouseDownCallback(RIGHT_BOTTOM_HANDLER_TYPE))

        element.appendChild(leftTopResizeController)
        element.appendChild(leftBottomResizeController)
        element.appendChild(rightTopResizeController)
        element.appendChild(rightBottomResizeController)
    }

    private onMouseUp() {
        window.removeEventListener('mousemove', this.m_onMouseMoveCallback)
        window.removeEventListener('mouseup', this.m_onMouseUpCallback)
    }

    private onMouseMove(e: MouseEvent, type: string) {
        const canvasBounds = this.m_parentElement.getBoundingClientRect()
        const elemBounds = this.m_element.getBoundingClientRect()
        const mouseX = e.x - canvasBounds.left
        const mouseY = e.y - canvasBounds.top
        const left = elemBounds.left - canvasBounds.left
        const top = elemBounds.top - canvasBounds.top
        switch (type) {
            case LEFT_TOP_HANDLER_TYPE:
                this.m_controller.resizeShape(
                    mouseX,
                    mouseY,
                    left + elemBounds.width,
                    top + elemBounds.height,
                )
                break
            case RIGHT_TOP_HANDLER_TYPE:
                this.m_controller.resizeShape(
                    left,
                    mouseY,
                    mouseX,
                    top + elemBounds.height,
                )
                break
            case LEFT_BOTTOM_HANDLER_TYPE:
                this.m_controller.resizeShape(
                    mouseX,
                    top,
                    left  + elemBounds.width,
                    mouseY,
                )
                break
            case RIGHT_BOTTOM_HANDLER_TYPE:
                this.m_controller.resizeShape(
                    left,
                    top,
                    mouseX,
                    mouseY,
                )
                break
        }
    }

    private buildOnMouseDownCallback(type: string) {
        return (e: MouseEvent) => {
            e.preventDefault()
            this.m_onMouseMoveCallback = (e) => {this.onMouseMove(e, type)}
            this.m_onMouseUpCallback = () => {this.onMouseUp()}
            window.addEventListener('mousemove', this.m_onMouseMoveCallback)
            window.addEventListener('mouseup', this.m_onMouseUpCallback)
        }
    }
}

export {
    ResizeHandler
}