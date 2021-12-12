"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Shape = void 0;
var Signal_1 = require("../Signal");
var Shape = /** @class */ (function () {
    function Shape(width, height, top, left) {
        this.onPositionChange = new Signal_1.Signal();
        this.onResizeChange = new Signal_1.Signal();
        this.m_width = width;
        this.m_height = height;
        this.m_left = left;
        this.m_top = top;
    }
    Shape.prototype.getOnPositionChange = function () {
        return this.onPositionChange;
    };
    Shape.prototype.getOnResizeChange = function () {
        return this.onResizeChange;
    };
    Object.defineProperty(Shape.prototype, "width", {
        get: function () {
            return this.m_width;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shape.prototype, "height", {
        get: function () {
            return this.m_height;
        },
        enumerable: false,
        configurable: true
    });
    Shape.prototype.setPosition = function (left, top) {
        this.m_top = top;
        this.m_left = left;
        this.onPositionChange.dispatch();
    };
    Shape.prototype.setSize = function (width, height) {
        this.m_width = width;
        this.m_height = height;
        this.onResizeChange.dispatch();
    };
    Object.defineProperty(Shape.prototype, "left", {
        get: function () {
            return this.m_left;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(Shape.prototype, "top", {
        get: function () {
            return this.m_top;
        },
        enumerable: false,
        configurable: true
    });
    return Shape;
}());
exports.Shape = Shape;
//# sourceMappingURL=Shape.js.map