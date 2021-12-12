"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ShapeRenderer = void 0;
var ShapeRenderer = /** @class */ (function () {
    function ShapeRenderer(model) {
        var _this = this;
        this.m_element = document.createElement('div');
        this.canvasLeftDx = 0;
        this.canvasTopDx = 0;
        this.leftDx = 0;
        this.topDx = 0;
        this.m_model = model;
        this.m_controller = new ShapeController(model, this);
        this.m_model.getOnPositionChange().add(function (_a) {
            var x = _a.x, y = _a.y;
            _this.setPosition(x, y);
        });
    }
    Object.defineProperty(ShapeRenderer.prototype, "model", {
        get: function () {
            return this.m_model;
        },
        enumerable: false,
        configurable: true
    });
    ShapeRenderer.prototype.onShapeMouseUp = function (e) {
        window.onmousemove = null;
        window.onmouseup = null;
        this.leftDx = 0;
        this.topDx = 0;
    };
    ShapeRenderer.prototype.onShapeMove = function (e) {
        this.m_controller.setPosition(e.x - this.canvasLeftDx - this.leftDx, e.y - this.canvasTopDx - this.topDx);
    };
    ShapeRenderer.prototype.onShapeMouseDown = function (e) {
        var _this = this;
        var elementBounds = this.m_element.getBoundingClientRect();
        this.leftDx = e.x - elementBounds.left;
        this.topDx = e.y - elementBounds.top;
        window.onmousemove = function (e) { return _this.onShapeMove(e); };
        window.onmouseup = function (e) { return _this.onShapeMouseUp(e); };
    };
    ShapeRenderer.prototype.setPosition = function (left, top) {
        this.m_element.style.left = left + 'px';
        this.m_element.style.top = top + 'px';
    };
    ShapeRenderer.prototype.render = function (canvas) {
        var _this = this;
        var canvasBounds = canvas.getBoundingClientRect();
        this.canvasLeftDx = canvasBounds.left;
        this.canvasTopDx = canvasBounds.top;
        var left = this.m_model.left;
        var top = this.m_model.top;
        var width = this.m_model.width;
        var height = this.m_model.height;
        this.m_element.style.left = left + 'px';
        this.m_element.style.top = top + 'px';
        this.m_element.style.width = width + 'px';
        this.m_element.style.height = height + 'px';
        this.m_element.style.position = 'absolute';
        this.m_element.onmousedown = function (e) { return _this.onShapeMouseDown(e); };
        this.m_element.innerHTML = this.getShapeHtmlImpl();
        canvas.appendChild(this.m_element);
    };
    return ShapeRenderer;
}());
exports.ShapeRenderer = ShapeRenderer;
//# sourceMappingURL=Shape.js.map