"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ShapeRenderer = void 0;
var ShapeController_1 = require("./ShapeController");
var ShapeRenderer = /** @class */ (function () {
    function ShapeRenderer(model, canvas) {
        var _this = this;
        this.m_element = document.createElement('div');
        this.m_model = model;
        this.m_controller = new ShapeController_1.ShapeController(model, this);
        this.m_canvas = canvas;
        this.m_model.getOnPositionChange().add(function () { return _this.rerender(); });
        this.m_model.getOnResizeChange().add(function () { return _this.rerender(); });
    }
    Object.defineProperty(ShapeRenderer.prototype, "model", {
        get: function () {
            return this.m_model;
        },
        enumerable: false,
        configurable: true
    });
    ShapeRenderer.prototype.onShapeMouseUp = function (e, leftOffset, topOffset) {
        window.onmousemove = null;
        window.onmouseup = null;
        this.m_controller.setPosition(e.x - leftOffset, e.y - topOffset);
    };
    ShapeRenderer.prototype.onShapeMove = function (e, leftOffset, topOffset) {
        this.m_controller.setPosition(e.x - leftOffset, e.y - topOffset);
    };
    ShapeRenderer.prototype.onShapeMouseDown = function (e, canvasLeftOffset, canvasTopOffset) {
        var _this = this;
        var elementBounds = this.m_element.getBoundingClientRect();
        var resultLeftOffset = canvasLeftOffset + (e.x - elementBounds.left);
        var resultTopOffset = canvasTopOffset + (e.y - elementBounds.top);
        window.onmousemove = function (e) { return _this.onShapeMove(e, resultLeftOffset, resultTopOffset); };
        window.onmouseup = function (e) { return _this.onShapeMouseUp(e, resultLeftOffset, resultTopOffset); };
    };
    ShapeRenderer.customizeControllers = function (handler, handlerType) {
        handler.style.width = '5px';
        handler.style.height = '5px';
        handler.style.position = 'absolute';
        handler.style.background = 'blue';
        switch (handlerType) {
            case "leftBottom":
                handler.style.bottom = '-2px';
                handler.style.left = '-2px';
                break;
            case "leftTop":
                handler.style.top = '-2px';
                handler.style.left = '-2px';
                break;
            case "rightBottom":
                handler.style.bottom = '-2px';
                handler.style.right = '-2px';
                break;
            case "rightTop":
                handler.style.top = '-2px';
                handler.style.right = '-2px';
                break;
        }
    };
    ShapeRenderer.prototype.addResizeHandlers = function (element, canvasBounds) {
        var leftTopResizeController = document.createElement('div');
        var rightTopResizeController = document.createElement('div');
        var leftBottomResizeController = document.createElement('div');
        var rightBottomResizeController = document.createElement('div');
        ShapeRenderer.customizeControllers(leftTopResizeController, 'leftTop');
        ShapeRenderer.customizeControllers(rightTopResizeController, 'rightTop');
        ShapeRenderer.customizeControllers(leftBottomResizeController, 'leftBottom');
        ShapeRenderer.customizeControllers(rightBottomResizeController, 'rightBottom');
        var handlerMouseMove = function (e, type) {
            var mouseLeft = e.x - canvasBounds.left;
            var mouseTop = e.y - canvasBounds.top;
            if (type === "leftTop") {
            }
            else if (type === "rightTop") {
            }
            else if (type === "leftBottom") {
            }
            else if (type === "rightBottom") {
            }
        };
        rightTopResizeController.onmousedown = function (e) {
            e.preventDefault();
            window.onmousemove = function () { };
        };
        element.appendChild(leftTopResizeController);
        element.appendChild(rightTopResizeController);
        element.appendChild(leftBottomResizeController);
        element.appendChild(rightBottomResizeController);
    };
    ShapeRenderer.prototype.rerender = function () {
        var left = this.m_model.left;
        var top = this.m_model.top;
        var width = this.m_model.width;
        var height = this.m_model.height;
        this.m_element.style.left = left + "px";
        this.m_element.style.top = top + "px";
        this.m_element.style.width = width + "px";
        this.m_element.style.height = height + "px";
        this.m_element.style.position = 'absolute';
        var svg = this.m_element.getElementsByTagName('svg')[0];
        if (svg) {
            svg.outerHTML = this.getShapeHtmlImpl();
        }
        else {
            this.m_element.innerHTML = this.getShapeHtmlImpl();
        }
    };
    ShapeRenderer.prototype.render = function () {
        var _this = this;
        this.m_element.remove();
        var canvasBounds = this.m_canvas.getBoundingClientRect();
        this.rerender();
        this.addResizeHandlers(this.m_element);
        this.m_element.onmousedown = function (e) { return _this.onShapeMouseDown(e, canvasBounds.left, canvasBounds.top); };
        this.m_canvas.appendChild(this.m_element);
    };
    return ShapeRenderer;
}());
exports.ShapeRenderer = ShapeRenderer;
//# sourceMappingURL=ShapeRenderer.js.map